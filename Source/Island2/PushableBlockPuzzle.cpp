#include "PushableBlockPuzzle.h"
#include <string>
#include "PuzzleTileComponent.h"
#include "PushableBlockTile.h"
#include "PushableBlock2.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APushableBlockPuzzle::APushableBlockPuzzle()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	PrimaryActorTick.bCanEverTick = true;
	Id = 0;
}

void APushableBlockPuzzle::BeginPlay()
{
	InitializeWithSize(Width, Height);
	InitializeBlocks();
	InitializeObstacles();
	InitializeGoals();
	Super::BeginPlay();
}

void APushableBlockPuzzle::InitializeBlocks()
{
	int i = 0;
	for (auto &block : PushableBlocks)
	{
		block->Id = i++;
		auto location = block->GetActorLocation();
		InitializeLocation(location, 1);
	}
}

void APushableBlockPuzzle::InitializeGoals()
{
	for (auto& goal : Goals)
	{
		auto location = goal->GetActorLocation();
		InitializeLocation(location, -1);
	}
}

void APushableBlockPuzzle::InitializeObstacles()
{
	for (auto& obstacle : Obstacles)
	{
		auto location = obstacle->GetActorLocation();
		InitializeLocation(location, 2);
	}
}
void APushableBlockPuzzle::InitializeLocation(FVector &location, int32 value)
{
	auto coordinates = GetCoordinates(location);
	if (IsValidCell(coordinates.Key, coordinates.Value))
	{
		Cells[coordinates.Key][coordinates.Value] = value;
	}
}

void APushableBlockPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#if WITH_EDITOR
void APushableBlockPuzzle::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName width = FName("Width");
	const FName height = FName("Height");
	const FName obstacles = FName("Obstacles");
	const FName goals = FName("Goals");
	const FName blocks = FName("Blocks");
	FName propertyName = PropertyChangedEvent.GetPropertyName();
	if (propertyName != width &&
		propertyName != height &&
		propertyName != obstacles &&
		propertyName != goals &&
		propertyName != blocks)
	{
		return;
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateTiles();
}
#endif

void APushableBlockPuzzle::UpdateTiles()
{
	ClearTiles();
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			CreateTile(x, y);
		}
	}
}

void APushableBlockPuzzle::Destroyed()
{
	ClearTiles();
}

void APushableBlockPuzzle::CreateTile(const int x, const int y)
{
	auto name = "Tile " + std::to_string(x) + " " + std::to_string(y);
	
	auto location = GetActorLocation();
	auto tile = NewObject<UPuzzleTileComponent>(this, FName(name.c_str()));
	tile->RegisterComponent();
	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->SetWorldLocation(FVector(x * 100, y * 100, 0) + location);
	Tiles.Add(tile);
	tile->UpdateMaterial();
}

FVector APushableBlockPuzzle::GetLocation(int x, int y) const
{
	return FVector(x * 100, y * 100, 101) + GetActorLocation();
}

void APushableBlockPuzzle::ClearTiles()
{
	for (auto &tile : Tiles)
	{
		tile->DestroyComponent();
	}
	Tiles.Empty();
}

void APushableBlockPuzzle::Push(int index, EBlockSide side)
{
	for (auto& block : PushableBlocks)
	{
		if (block->Id != index)
		{
			continue;
		}
		
		FVector location = block->GetActorLocation();
		const TTuple<int32, int32> coordinates = GetCoordinates(location);
		block->X = coordinates.Key;
		block->Y = coordinates.Value;
		auto newCoordinates = PushBlockInDirection(block->X, block->Y, side);
		block->X = newCoordinates.Key;
		block->Y = newCoordinates.Value;
		auto newLocation = GetLocation(newCoordinates.Key, newCoordinates.Value);
		block->SetActorLocation(newLocation);
	}
}

void APushableBlockPuzzle::UpdateLocation(APushableBlock2* block)
{
	auto location = GetLocation(block->X, block->Y);
	block->SetActorLocation(location);
}

TTuple<int32, int32> APushableBlockPuzzle::PushBlockInDirection(int x, int y, EBlockSide side)
{
	int xDir = GetXDir(side);
	int yDir = GetYDir(side);
	if (!IsValidCell(x, y))
	{
		return TTuple<int32, int32>(-1, -1);
	}
	
	Cells[x][y] = 0;
	while (IsValidMove(x + xDir, y + yDir))
	{
		x += xDir;
		y += yDir;
	}
	
	Cells[x][y] = 1;

	return TTuple<int32, int32>(x, y);
}

int APushableBlockPuzzle::GetXDir(EBlockSide side)
{
	if (side == EBlockSide::Left)
	{
		return 1;
	}
	if (side == EBlockSide::Right)
	{
		return -1;
	}
	return 0;
}

int APushableBlockPuzzle::GetYDir(EBlockSide side)
{
	if (side == EBlockSide::Front)
	{
		return 1;
	}
	if (side == EBlockSide::Back)
	{
		return -1;
	}
	return 0;
}

bool APushableBlockPuzzle::IsValidCell(int x, int y)
{
	return x >= 0 && x < Width && y >= 0 && y < Height;
}

bool APushableBlockPuzzle::IsValidMove(int x, int y)
{
	return IsValidCell(x, y) && Cells[x][y] <= 0;
}

void APushableBlockPuzzle::InitializeWithSize(int width, int height)
{
	Cells = new int* [width];
	for (int i = 0; i < width; i++)
		Cells[i] = new int[height];


	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			Cells[i][j] = 0;
		}
}

TTuple<int32, int32> APushableBlockPuzzle::GetCoordinates(FVector& location) const
{
	const FVector offset = location - GetActorLocation();
	double x = offset.X / 100.0;
	double y = offset.Y / 100.0;
	return TTuple<int32, int32>(x, y);
}
