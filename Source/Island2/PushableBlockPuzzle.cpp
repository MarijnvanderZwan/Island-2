#include "PushableBlockPuzzle.h"
#include <string>
#include "PuzzleTileComponent.h"
#include "PushableBlockTile.h"

// Sets default values
APushableBlockPuzzle::APushableBlockPuzzle()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	PrimaryActorTick.bCanEverTick = true;
}

void APushableBlockPuzzle::BeginPlay()
{
	Super::BeginPlay();
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
	UE_LOG(LogTemp, Warning, TEXT("UPDATE!"));
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateTiles();
}
#endif

void APushableBlockPuzzle::Destroyed()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
	ClearTiles();
}

void APushableBlockPuzzle::ParseObstacles()
{
	for (auto& obstacle : Obstacles)
	{
		auto tuple = Parse(obstacle);
		if (tuple.Key >= 0)
		{
			ParsedObstacles.Add(tuple);
		}
	}
}

void APushableBlockPuzzle::ParseGoals()
{
	for (auto& goal : Goals)
	{
		auto tuple = Parse(goal);
		if (tuple.Key >= 0)
		{
			ParsedGoals.Add(tuple);
		}
	}
}

void APushableBlockPuzzle::ParseBlocks()
{
	for (auto& block : Blocks)
	{
		auto tuple = Parse(block);
		if (tuple.Key >= 0)
		{
			ParsedBlocks.Add(tuple);
		}
	}
}

void APushableBlockPuzzle::UpdateTiles()
{
	ClearTiles();

	ParseObstacles();
	ParseGoals();
	ParseBlocks();
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			auto tuple = TTuple<int32, int32>(x, y);
			if (ParsedObstacles.Contains(tuple))
			{
				CreateTile(x, y, ETileType::Blocking);
			}
			else if (ParsedGoals.Contains(tuple))
			{
				CreateTile(x, y, ETileType::Goal);
			}
			else
			{
				CreateTile(x, y, ETileType::Empty);
			}
		}
	}

	for (auto& block : ParsedBlocks)
	{
		CreateBlock(block.Key, block.Value);
	}
}

void APushableBlockPuzzle::CreateTile(const int x, const int y, ETileType tileType)
{
	UE_LOG(LogTemp, Warning, TEXT("%i %i"), x, y);
	auto name = std::to_string(x) + " " + std::to_string(y);
	
	auto location = GetActorLocation();
	auto tile = NewObject<UPuzzleTileComponent>(this, FName(name.c_str()));
	tile->RegisterComponent();
	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->SetWorldLocation(FVector(x * 100, y * 100, 0) + location);
	Tiles.Add(tile);
	tile->EmptyColor = EmptyColor;
	tile->BlockingColor = BlockingColor;
	tile->GoalColor = GoalColor;
	tile->TileType = tileType;
	tile->UpdateMaterial();
	/*

	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("%i"), RootComponent->GetNumChildrenComponents());
	//Tiles.push_back(*tile);
	//Tiles.Add(tile);*/
}

void APushableBlockPuzzle::CreateBlock(const int x, const int y)
{
	UE_LOG(LogTemp, Warning, TEXT("%i %i"), x, y);
	auto name = std::to_string(x) + " " + std::to_string(y);

	auto location = GetActorLocation();
	auto tile = NewObject<UPuzzleTileComponent>(this, FName(name.c_str()));
	tile->RegisterComponent();
	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->SetWorldLocation(FVector(x * 100, y * 100, 100) + location);
	Tiles.Add(tile);
	tile->EmptyColor = EmptyColor;
	tile->BlockingColor = BlockingColor;
	tile->GoalColor = GoalColor;
	tile->UpdateMaterial();
	/*

	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("%i"), RootComponent->GetNumChildrenComponents());
	//Tiles.push_back(*tile);
	//Tiles.Add(tile);*/
}

TTuple<int32, int32> APushableBlockPuzzle::Parse(FString str)
{
	if (str.Len() < 3)
	{
		return TTuple<int32, int32>(-1, -1);
	}
	int index = str.Find(" ");
	FString xstr = str.Mid(0, index);
	FString ystr = str.Mid(index, str.Len() - index);
	int32 x = FCString::Atoi(*xstr);
	int32 y = FCString::Atoi(*ystr);
	return TTuple<int32, int32>(x, y);
}


void APushableBlockPuzzle::ClearTiles()
{
	for (auto& tile : Tiles)
	{
		tile->DestroyComponent();
	}
	Tiles.Empty();
	ParsedObstacles.Empty();
	ParsedGoals.Empty();
	ParsedBlocks.Empty();
}