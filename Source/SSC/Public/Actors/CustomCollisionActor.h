// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CustomCollisionActor.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EShapeComponent : uint8
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
	void SetCollShape(EShapeComponent InCollisionShape);

	// TODO try and hide this from designers but still make it editable. I don't think it can be done.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
	UShapeComponent* CollisionShape;

	UPROPERTY(EditAnywhere)
	class UDealDamageComponent* DealDamageComponent;
	
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	EShapeComponent Shape = EShapeComponent::Sphere;
};
