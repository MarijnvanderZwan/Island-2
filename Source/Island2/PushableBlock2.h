// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EBlockSide.h"
#include "PushableBlock2.generated.h"

UCLASS()
class ISLAND2_API APushableBlock2 : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APushableBlock2();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly)
	int Id;

	UPROPERTY(VisibleAnywhere)
	int PuzzleId;

	UPROPERTY(VisibleAnywhere)
	int X;

	UPROPERTY(VisibleAnywhere)
	int Y;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	EBlockSide GetBlockSide(const FVector& otherLocation);
};
