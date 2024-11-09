#include "BT_CoinGameComponent.h"

#include "Kismet/KismetSystemLibrary.h"

UBT_CoinGameComponent::UBT_CoinGameComponent()
	: Super()
{
	SphereRadius = 90.f;
}

void UBT_CoinGameComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UBT_CoinGameComponent::OnSphereBeginOverlap);
}

void UBT_CoinGameComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		// Notify that the actor is being picked up
		OnCoinPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}

bool UBT_CoinGameComponent::IsLastCoin(int32& Count) const
{
	TInlineComponentArray<UBT_CoinGameComponent*, 100> CoinComponents{};
	for (TObjectIterator<UBT_CoinGameComponent> Itr; Itr; ++Itr)
	{
		if ((*Itr)->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject | RF_BeginDestroyed)
			|| (*Itr)->IsBeingDestroyed() || (*Itr) == this)
		{
			continue;
		}
		CoinComponents.Add(*Itr);
	}
	Count = CoinComponents.Num();
	return Count < 1;
}
