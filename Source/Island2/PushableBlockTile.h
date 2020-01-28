// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ETileType.h"
#include "PushableBlockTile.generated.h"

UCLASS()
class ISLAND2_API APushableBlockTile : public AActor
{
	GENERATED_BODY()
	
public:	
	APushableBlockTile();
	

protected:
	virtual void BeginPlay() override;
	
#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
#endif
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileType TileType;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FColor EmptyColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FColor BlockingColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FColor GoalColor;
	
	virtual void Tick(float DeltaTime) override;
	
	void UpdateMaterial();
};
