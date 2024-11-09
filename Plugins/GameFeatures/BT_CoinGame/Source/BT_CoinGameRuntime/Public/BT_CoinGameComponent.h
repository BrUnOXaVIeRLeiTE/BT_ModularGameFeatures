// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"

#include "BT_CoinGameComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinPickUp, ACharacter*, PickUpCharacter);

UCLASS(ClassGroup = BlackTower, Category = "Gameplay", BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "[BT] Coin Game Component"), hideCategories = ("Cooking", "Variable"))
class BT_COINGAMERUNTIME_API UBT_CoinGameComponent : public USphereComponent
{
	GENERATED_BODY()

	UBT_CoinGameComponent();

public:
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnCoinPickUp OnCoinPickUp;

protected:
	/** Called when the game starts */
	virtual void BeginPlay() override;

	/** Code for when something overlaps this component */
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool IsLastCoin(int32& Count) const;
};
