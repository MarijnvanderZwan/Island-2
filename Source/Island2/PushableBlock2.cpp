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

void APushableBlock2::Tick(float DeltaTime)
{
	if (IsMoving)
	{
		MoveTowardsTarget(DeltaTime);
	}
	Super::Tick(DeltaTime);
}

void APushableBlock2::MoveTowardsTarget(float DeltaTime)
{
	const float MovementSpeed = 500;
	const float Tolerance = 0.001;

	FVector currentLocation = GetActorLocation();
	FVector difference = (TargetLocation - currentLocation);
	float differenceLength = difference.Size();
	difference.Normalize();

	float distanceToMove = FMath::Min(MovementSpeed * DeltaTime, differenceLength);

	FVector nextLocation = currentLocation + difference * distanceToMove;
	SetActorLocation(nextLocation);
	if ((TargetLocation - nextLocation).Size() < Tolerance)
	{
		IsMoving = false;
		SetActorLocation(TargetLocation);
	}
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

void APushableBlock2::SetTargetLocation(const FVector& otherLocation)
{
	TargetLocation = otherLocation;
	IsMoving = true;
}
