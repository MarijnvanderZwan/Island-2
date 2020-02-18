// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTileComponent.h"
#include <vector>
#include "PushableBlock2.h"
#include "PushableBlockPuzzle.generated.h"

UCLASS()
class ISLAND2_API APushableBlockPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	APushableBlockPuzzle();
	
protected:
	virtual void BeginPlay() override;
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	TArray<UPuzzleTileComponent*> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APushableBlock2*> PushableBlocks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Goals;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Obstacles;

	int** Cells;
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor EmptyColor = FColor(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor BlockingColor = FColor(1, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor GoalColor = FColor(0, 1, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> TileTypes;

private:
	void UpdateTiles();
	void ClearTiles();
	void CreateTile(int x, int y);
	void InitializeLocation(FVector& location, int32 value);
	UFUNCTION(BlueprintCallable)
	void Push(int index, EBlockSide side);

	TTuple<int32, int32> PushBlockInDirection(int x, int y, EBlockSide side);
	TTuple<int32, int32> GetCoordinates(FVector& location) const;
	
	bool IsValidCell(int x, int y);

	bool IsValidMove(int x, int y);

	void InitializeWithSize(int width, int height);

	int GetXDir(EBlockSide side);
	int GetYDir(EBlockSide side);

	void UpdateLocation(APushableBlock2* block);

	FVector GetLocation(int x, int y) const;

	void InitializeBlocks();
	void InitializeObstacles();
	void InitializeGoals();
};