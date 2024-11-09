// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonAbilityTargetActor.h"
#include "FirstPerson/FirstPerson.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/BlueprintGeneratedClass.h"

void AFirstPersonAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
	
	RecieveStartTargeting(Ability);
}

bool AFirstPersonAbilityTargetActor::IsConfirmTargetingAllowed()
{
	return K2_IsConfirmTargetingAllowed();
}

void AFirstPersonAbilityTargetActor::ConfirmTargetingAndContinue()
{
	if (SourceActor && ensureAlways(ShouldProduceTargetData()))
	{
		auto ImplementedInBlueprint = [](const UFunction* Func) -> bool
		{
			return Func && ensure(Func->GetOuter())
				&& Func->GetOuter()->IsA(UBlueprintGeneratedClass::StaticClass());
		};
		UE_CLOG(
			!ImplementedInBlueprint(GetClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(AFirstPersonAbilityTargetActor, MakeTargetData))),
			LogFirstPerson,
			Error,
			TEXT("`%s` does not implement `MakeTargetData`. Invalid target data will be returned."),
			*GetClass()->GetName()
		);

		FGameplayAbilityTargetDataHandle Handle = MakeTargetData();
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

bool AFirstPersonAbilityTargetActor::K2_IsConfirmTargetingAllowed_Implementation()
{
	return Super::IsConfirmTargetingAllowed();
}