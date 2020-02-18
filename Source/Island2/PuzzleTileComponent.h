// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleTileComponent.generated.h"

/**
 * 
 */
UCLASS()
class ISLAND2_API UPuzzleTileComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UPuzzleTileComponent();

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
	
	void UpdateMaterial();
	void ClearTiles();
};
