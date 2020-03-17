#include "PushableBlockPuzzle.h"
#include <string>
#include "PuzzleTileComponent.h"
#include "PushableBlockTile.h"
#include "PushableBlock.h"
#include "Kismet/GameplayStatics.h"

APushableBlockPuzzle::APushableBlockPuzzle()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	PrimaryActorTick.bCanEverTick = true;
	Id = FGuid::NewGuid();
}

void APushableBlockPuzzle::BeginPlay()
{
	Grid = PushableBlockGrid(Width, Height);
	InitializeBlocks();
	InitializeObstacles();
	InitializeGoals();
	Super::BeginPlay();
}

void APushableBlockPuzzle::InitializeBlocks()
{
	int i = 0;
	for (APushableBlock*& block : PushableBlocks)
	{
		block->Id = i++;
		block->PuzzleId = Id;
		FVector location = block->GetActorLocation();
		InitializeLocation(location, 1);
	}
}

void APushableBlockPuzzle::InitializeGoals()
{
	for (AActor*& goal : Goals)
	{
		FVector location = goal->GetActorLocation();
		InitializeLocation(location, -1);
	}
}

void APushableBlockPuzzle::InitializeObstacles()
{
	for (AActor*& obstacle : Obstacles)
	{
		FVector location = obstacle->GetActorLocation();
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

FVector APushableBlockPuzzle::GetLocation(int x, int y) const
{
	return FVector(x * TileSize, y * TileSize, 0) + GetActorLocation();
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
	double x = offset.X / TileSize;
	double y = offset.Y / TileSize;
	return TTuple<int, int>(x, y);
}
