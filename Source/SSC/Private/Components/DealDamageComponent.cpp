// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DealDamageComponent.h"
#include "Actors/CustomCollisionActor.h"
#include "Components/ShapeComponent.h"
#include "Engine/DamageEvents.h"

UDealDamageComponent::UDealDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UDealDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	CustomCollisionActor = Cast<ACustomCollisionActor>(GetOwner());

	if (CustomCollisionActor)
	{
		if (CustomCollisionActor->CollisionShape)
		{
			CustomCollisionActor->CollisionShape->OnComponentBeginOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapBegin);
			CustomCollisionActor->CollisionShape->OnComponentEndOverlap.AddDynamic(this, &UDealDamageComponent::OnOverlapEnd);
		}
	}
	
	SetComponentTickEnabled(false);
}

void UDealDamageComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (OtherActor == GetOwner())
	{
		return;
	}
	
	DamageableActor = Cast<AActor>(OtherActor);
	
	if (DamageableActor)
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Magenta, FString::Printf(TEXT("Damage:  %f"), Damage));

		DamageableActor->TakeDamage(Damage, DamageEvent, nullptr, GetOwner());
		
		if (bDamageOverTime)
		{
			SetComponentTickEnabled(true);
			GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Blue, FString::Printf(TEXT("::OnOverlapBegin")));
		}
	}
}

void UDealDamageComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bDamageOverTime)
	{
		SetComponentTickEnabled(false);
		GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Red, FString::Printf(TEXT("::OnOverlapEnd")));
	}
}

void UDealDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimePassed += DeltaTime;
	
	if (bDamageOverTime)
	{
		if (DamageableActor)
		{
			if (TimePassed > TickInterval)
			{
				TimePassed = 0;
				TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
				FDamageEvent DamageEvent(ValidDamageTypeClass);
				DamageableActor->TakeDamage(TickDamage, DamageEvent, nullptr, GetOwner());
				
				GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Magenta, FString::Printf(TEXT("Tick damage:  %f"), TickDamage));
				
			}
		}
	}
}
