// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CustomCollisionActor.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EDamageShape : uint8
{
	Box,
	Sphere,
	Capsule
};

UCLASS()
class SSC_API ACustomCollisionActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	
	ACustomCollisionActor();

	UFUNCTION(BlueprintCallable)
	void SetCollShape(EDamageShape InCollisionShape);

	// TODO try and hide this from designers but still make it editable.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision", meta = (HideInDetailPanel = true))
	UShapeComponent* CollisionShape;

	UPROPERTY(EditAnywhere)
	class UDealDamageComponent* DealDamageComponent;
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	EDamageShape Shape = EDamageShape::Sphere;
};
