// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/CustomCollisionActor.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/DealDamageComponent.h" // Delete if not using

ACustomCollisionActor::ACustomCollisionActor()
{
	if (GetStaticMeshComponent())
	{
		RootComponent = GetStaticMeshComponent();
	}

	// Example showing a damage event will affect any Collision Shape.
	DealDamageComponent = CreateDefaultSubobject<UDealDamageComponent>(TEXT("Deal Damage Component"));
}

void ACustomCollisionActor::SetCollShape(EDamageShape InCollisionShape)
{
	if (CollisionShape != nullptr)
	{
		if (CollisionShape->IsRegistered())
		{
			CollisionShape->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
			CollisionShape->UnregisterComponent();
			CollisionShape->DestroyComponent(false);
		}
	}
	
	switch (InCollisionShape)
	{
	case (EDamageShape::Box):
		{
			UBoxComponent* BoxComponent = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), "boxcomp");
			if (BoxComponent)
			{
				BoxComponent->SetBoxExtent(FVector(200.0f,200.0f,200.f));
				CollisionShape = BoxComponent;
			}
			break;
		}
	case (EDamageShape::Sphere):
		{
			USphereComponent* SphereComponent = NewObject<USphereComponent>(this, USphereComponent::StaticClass(), "SphereComp");
			if (SphereComponent)
			{
				SphereComponent->SetSphereRadius(100.0f);
				CollisionShape = SphereComponent;
			}
			break;
		}
	case (EDamageShape::Capsule):
		{
			UCapsuleComponent* CapsuleComponent = NewObject<UCapsuleComponent>(this, UCapsuleComponent::StaticClass(), "CapsuleComp");
			if (CapsuleComponent)
			{
				CapsuleComponent->SetCapsuleRadius(100.0f);
				CapsuleComponent->SetCapsuleHalfHeight(200.0f);
				CollisionShape = CapsuleComponent;
			}
			break;
		}
	}
	if (CollisionShape != nullptr)
	{
		CollisionShape->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CollisionShape->SetHiddenInGame(false);
		CollisionShape->SetVisibility(true);
		CollisionShape->bUseAsOccluder = true;
		if (!CollisionShape->IsRegistered())
		{
			CollisionShape->RegisterComponent();
		}
		UE_LOG(LogTemp, Warning, TEXT("Set shape to box: %s"), *CollisionShape->GetName())
	}
}

// Adjust the switch logic in SetCollShape so it does not change Shape after edit
#if WITH_EDITOR
void ACustomCollisionActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName const PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	FName const MemberName = GET_MEMBER_NAME_CHECKED(ACustomCollisionActor, Shape);
	if (PropertyName == MemberName)
	{
		SetCollShape(Shape);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor prop changed but not what we are looking for"));
	}
}
#endif
