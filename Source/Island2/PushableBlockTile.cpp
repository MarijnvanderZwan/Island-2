// Fill out your copyright notice in the Description page of Project Settings.

#include "PushableBlockTile.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APushableBlockTile::APushableBlockTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/Blueprints/Cube.Cube'"));
	Mesh->SetStaticMesh(ModelPath.Object);
}

// Called when the game starts or when spawned
void APushableBlockTile::BeginPlay()
{
	Super::BeginPlay();
	
}

#if WITH_EDITOR
void APushableBlockTile::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName triggerUpdate = FName("TileType");
	FName propertyName = PropertyChangedEvent.GetPropertyName();
	if (propertyName != triggerUpdate)
	{
		return;
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateMaterial();
}
#endif

// Called every frame
void APushableBlockTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APushableBlockTile::UpdateMaterial()
{
	UMaterialInterface* Material = Mesh->GetMaterial(0);
	UMaterialInstanceDynamic* matInstance = Mesh->CreateDynamicMaterialInstance(0, Material);

	if (matInstance == nullptr)
	{
		return;
	}
	switch (TileType)
	{
		case ETileType::Empty:
			matInstance->SetVectorParameterValue("Color", EmptyColor);
			break;
		case ETileType::Blocking:
			matInstance->SetVectorParameterValue("Color", BlockingColor);
			break;
		case ETileType::Goal:
			matInstance->SetVectorParameterValue("Color", GoalColor);
			break;
		default:
			break;
	}
}

