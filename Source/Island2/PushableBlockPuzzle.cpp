#include "PushableBlockPuzzle.h"
#include <string>
#include "PuzzleTileComponent.h"
#include "PushableBlockTile.h"
#include "PushableBlock.h"
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
	Grid = PushableBlockGrid(Width, Height);

	//InitializeWithSize(Width, Height);
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
	Grid.InitializeLocation(coordinates.Key, coordinates.Value, value);
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
	auto block = GetBlock(index);
	if (block == nullptr)
	{
		return;
	}
	
	FVector location = block->GetActorLocation();
	const TTuple<int, int> coordinates = GetCoordinates(location);
	block->X = coordinates.Key;
	block->Y = coordinates.Value;

	auto newCoordinates = Grid.PushBlockInDirection(block->X, block->Y, side);
	block->X = std::get<0>(newCoordinates);
	block->Y = std::get<1>(newCoordinates);
	auto newLocation = GetLocation(block->X, block->Y);
	block->SetTargetLocation(newLocation);

	if (Grid.PuzzleIsComplete())
	{
		UE_LOG(LogTemp, Warning, TEXT("Puzzle complete"));
	}
}

APushableBlock* APushableBlockPuzzle::GetBlock(int index)
{
	for (APushableBlock*& block : PushableBlocks)
	{
		if (block->Id == index && !block->IsMoving)
		{
			return block;
		}
	}
	return nullptr;
}

TTuple<int, int> APushableBlockPuzzle::GetCoordinates(FVector& location) const
{
	const FVector offset = location - GetActorLocation();
	double x = offset.X / 100.0;
	double y = offset.Y / 100.0;
	return TTuple<int, int>(x, y);
}
