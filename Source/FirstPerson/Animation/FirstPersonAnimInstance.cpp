// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonAnimInstance.h"
#include "AbilitySystemComponent.h"

void UFirstPersonAnimInstance::NativeInitializeAnimation()
{
	if (AActor* MyActor = GetOwningActor())
	{
		UAbilitySystemComponent* AbilityComponent = MyActor->FindComponentByClass<UAbilitySystemComponent>();
		if (AbilityComponent)
		{
			InitializeWithAbilitySystem(AbilityComponent);
		}
	}

	Super::NativeInitializeAnimation();
}

void UFirstPersonAnimInstance::InitializeWithAbilitySystem(UAbilitySystemComponent* AbilityComponent)
{
	GameplayTagPropertyMap.Initialize(this, AbilityComponent);
	ReceiveAbilitySystem(AbilityComponent);
}