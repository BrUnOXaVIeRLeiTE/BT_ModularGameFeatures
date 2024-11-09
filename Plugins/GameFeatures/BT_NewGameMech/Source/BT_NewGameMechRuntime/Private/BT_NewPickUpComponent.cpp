// Copyright Epic Games, Inc. All Rights Reserved.

#include "BT_NewPickUpComponent.h"

UBT_NewPickUpComponent::UBT_NewPickUpComponent()
{
	SphereRadius = 90.f;
}

void UBT_NewPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UBT_NewPickUpComponent::OnSphereBeginOverlap);
}

void UBT_NewPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
