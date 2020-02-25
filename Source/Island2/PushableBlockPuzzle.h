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
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	TArray<UPuzzleTileComponent*> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APushableBlock*> PushableBlocks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Goals;
UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Obstacles;

	//int** Cells;
	PushableBlockGrid Grid;
	int Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerUpdate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> TileTypes;

private:
	void UpdateTiles();
	void ClearTiles();
	void CreateTile(int x, int y);
	void InitializeLocation(FVector& location, int32 value);
	UFUNCTION(BlueprintCallable)
	void Push(int index, EBlockSide side);

	//TTuple<int32, int32> PushBlockInDirection(int x, int y, EBlockSide side);
	TTuple<int, int> GetCoordinates(FVector& location) const;
	
	//bool IsValidCell(std::tuple<int, int> tuple);
	//bool IsValidMove(int x, int y);
	//void InitializeWithSize(int width, int height);

	//int GetXDir(EBlockSide side);
	//int GetYDir(EBlockSide side);

	void UpdateLocation(APushableBlock* block);

	FVector GetLocation(int x, int y) const;

	void InitializeBlocks();
	void InitializeObstacles();
	void InitializeGoals();

	APushableBlock* GetBlock(int index);
};