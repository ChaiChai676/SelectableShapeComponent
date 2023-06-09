#include "Actors/SSCActor.h"
#include "Components/ShapeComponent.h"

ASSCActor::ASSCActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = RootComp;
	ShapeComponent = CreateDefaultSubobject<UShapeComponent>(TEXT("Shape Component"));
	
	if (ShapeComponent)
	{
		ShapeComponent->SetupAttachment(RootComponent);
	}

	// SpawnedShape = Cast<UShapeComponent>(ShapeComponent);
	
	// TODO Jeff - create the ShapeComponent in the constructor
	// TODO Jeff - create a custom ShapeComponent
	// TODO Jeff - get a reference to the ShapeComponent spawned (pointer)
}

void ASSCActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	// TODO Jeff - delete SpawnedShape if there is one, then reassign SpawnedShape to ShapeComponent
	// FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	// if (PropertyName == GET_MEMBER_NAME_CHECKED(ADamagingActor, ShapeComponent))
	// {
	// 	// ShapeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// }
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	// if (!PreviousShapeComponent)
	// {
	// 	PreviousShapeComponent = ShapeComponent;
	// }
	
	// if(ShapeComponent != PreviousShapeComponent)
	// {
		// ShapeComponent->DestroyComponent();
		// ShapeComponent = NewObject<UShapeComponent>(this, ChangedShapeComponent);
		// ShapeComponent->RegisterComponent();
		// ShapeComponent->SetCollisionProfileName(TEXT("Pawn"));
		// ShapeComponent->SetVisibility(true);
		// ShapeComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	// }
}