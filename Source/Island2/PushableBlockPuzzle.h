// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTileComponent.h"
#include <vector>
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
	TArray<FString> Obstacles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Goals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Blocks;
	
	TArray<TTuple<int32, int32>> ParsedObstacles;
	TArray<TTuple<int32, int32>> ParsedGoals;
	TArray<TTuple<int32, int32>> ParsedBlocks;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerUpdate;
	
	//TArray<UPuzzleTileComponent*> Tiles;

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
	void CreateTile(int x, int y, ETileType tileType);
	void CreateBlock(int x, int y);
	TTuple<int32, int32> Parse(FString str);
	void ParseObstacles();
	void ParseGoals();
	void ParseBlocks();
};