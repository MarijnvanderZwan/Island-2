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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Tiles;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TriggerUpdate;
	
	//TArray<UPuzzleTileComponent*> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor EmptyColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor BlockingColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor GoalColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> TileTypes;

private:
	void UpdateTile();
	void UpdateTiles();
	void ClearTiles();
	void CreateTile(int x, int y);
};