// Fill out your copyright notice in the Description page of Project Settings.
#include "PushableBlock2.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APushableBlock2::APushableBlock2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/Blueprints/Cube.Cube'"));
	Mesh->SetStaticMesh(ModelPath.Object);
}

// Called when the game starts or when spawned
void APushableBlock2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APushableBlock2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

EBlockSide APushableBlock2::GetBlockSide(const FVector& otherLocation)
{
	auto location = GetActorLocation();
	auto difference = otherLocation - location;
	auto relative = GetActorRotation().GetInverse().RotateVector(difference);
	bool xGreaterThanY = FMath::Abs(relative.X) > FMath::Abs(relative.Y);
	if (relative.X < 0 && xGreaterThanY)
	{
		return EBlockSide::Left;
	}
	if (relative.Y < 0 && !xGreaterThanY)
	{
		return EBlockSide::Front;
	}
	if (relative.X > 0 && xGreaterThanY)
	{
		return EBlockSide::Right;
	}
	return EBlockSide::Back;
}