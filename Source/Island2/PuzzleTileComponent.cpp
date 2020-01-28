// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTileComponent.h"
#include "UObject/ConstructorHelpers.h"

UPuzzleTileComponent::UPuzzleTileComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ModelPath(TEXT("StaticMesh'/Game/Blueprints/Cube.Cube'"));
	SetStaticMesh(ModelPath.Object);
}

#if WITH_EDITOR
void UPuzzleTileComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	const FName triggerUpdate = FName("TileType");
	FName propertyName = PropertyChangedEvent.GetPropertyName();
	if (propertyName != triggerUpdate)
	{
		return;
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UpdateMaterial();
}
#endif

void UPuzzleTileComponent::UpdateMaterial()
{
	UMaterialInterface* Material = GetMaterial(0);
	UMaterialInstanceDynamic* matInstance = CreateDynamicMaterialInstance(0, Material);

	if (matInstance == nullptr)
	{
		return;
	}
	switch (TileType)
	{
	case ETileType::Empty:
		matInstance->SetVectorParameterValue("Color", EmptyColor);
		break;
	case ETileType::Blocking:
		matInstance->SetVectorParameterValue("Color", BlockingColor);
		break;
	case ETileType::Goal:
		matInstance->SetVectorParameterValue("Color", GoalColor);
		break;
	default:
		break;
	}
}