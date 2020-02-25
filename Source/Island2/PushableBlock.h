// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EBlockSide.h"
#include "PushableBlock.generated.h"

UCLASS()
class ISLAND2_API APushableBlock : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APushableBlock();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly)
	int Id;

	UPROPERTY(VisibleAnywhere)
	int PuzzleId;

	int X;
	int Y;

	FVector TargetLocation;

	bool IsMoving;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EBlockSide GetBlockSide(const FVector& otherLocation);

	void SetTargetLocation(const FVector& otherLocation);

private:
	void MoveTowardsTarget(float DeltaTime);
};
