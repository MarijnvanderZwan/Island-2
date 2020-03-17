// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTileComponent.h"
#include <vector>
#include "PushableBlock.h"
#include "PushableBlockGrid.h"
#include "PushableBlockPuzzle.generated.h"

UCLASS()
class ISLAND2_API APushableBlockPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	APushableBlockPuzzle();
	
protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APushableBlock*> PushableBlocks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Goals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Obstacles;

	PushableBlockGrid Grid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGuid Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;

private:
	void InitializeLocation(FVector& location, int32 value);
	UFUNCTION(BlueprintCallable)
	void Push(int index, EBlockSide side);

	TTuple<int, int> GetCoordinates(FVector& location) const;
	
	FVector GetLocation(int x, int y) const;

	void InitializeBlocks();
	void InitializeObstacles();
	void InitializeGoals();

	APushableBlock* GetBlock(int index);

	const double TileSize = 200;
};