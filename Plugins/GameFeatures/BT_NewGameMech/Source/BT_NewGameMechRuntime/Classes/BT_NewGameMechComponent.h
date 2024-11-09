// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Components/ActorComponent.h"

#include "BT_NewGameMechComponent.generated.h"

UCLASS(ClassGroup = BlackTower, Category = "Gameplay", BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent, DisplayName = "[BT] Jetpack Component"), hideCategories = ("Cooking", "Variable"))
class BT_NEWGAMEMECHRUNTIME_API UJetpackComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UInputAction> JetpackMoveAction;

public:
	UJetpackComponent();
	virtual void PostLoad() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	/** Called for movement input */
	void JetpackMove(const FInputActionValue& Value);
};
