#include "PushableBlockPuzzle.h"
#include <string>
#include "PuzzleTileComponent.h"
#include "PushableBlockTile.h"

// Sets default values
APushableBlockPuzzle::APushableBlockPuzzle()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
}

void APushableBlockPuzzle::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Begin play called"));
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
	FName propertyName = PropertyChangedEvent.GetPropertyName();
	if (propertyName != width && propertyName != height)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UPDATE!"));
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateTiles();
	//UpdateTile();
}
#endif

void APushableBlockPuzzle::Destroyed()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroyed"));
	ClearTiles();
}

void APushableBlockPuzzle::UpdateTile()
{
	ClearTiles();

	for (int x = 0; x < 1; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			CreateTile(x, y);
		}
	}
}

void APushableBlockPuzzle::UpdateTiles()
{
	for (int x = 0; x < Width; x++)
	{
		for (int y = 0; y < Height; y++)
		{
			CreateTile(x, y);
		}
	}
}

void APushableBlockPuzzle::CreateTile(int x, int y)
{
	UE_LOG(LogTemp, Warning, TEXT("%i %i"), x, y);
	auto name = std::to_string(x) + " " + std::to_string(y);
	
	auto location = GetActorLocation();
	auto tile = NewObject<UPuzzleTileComponent>(this, FName(name.c_str()));
	tile->RegisterComponent();
	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->SetWorldLocation(FVector(x * 200, y * 200, 0) + location);
	/*
	tile->EmptyColor = EmptyColor;
	tile->BlockingColor = BlockingColor;
	tile->GoalColor = GoalColor;
	tile->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	tile->InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("%i"), RootComponent->GetNumChildrenComponents());
	//Tiles.push_back(*tile);
	//Tiles.Add(tile);*/
}


void APushableBlockPuzzle::ClearTiles()
{/*
	for (auto& tile : Tiles)
	{
		tile->DestroyComponent();
	}
	Tiles.Empty();*/
}