#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SSCActor.generated.h"

UCLASS()
class SSC_API ASSCActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASSCActor();
	
	USceneComponent* RootComp;
	AActor* SpawnedShape;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UShapeComponent> ShapeComponent;

	TObjectPtr<UShapeComponent> PreviousShapeComponent;
	
};
