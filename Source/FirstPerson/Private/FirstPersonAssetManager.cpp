// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonAssetManager.h"
#include "AbilitySystemGlobals.h"

void UFirstPersonAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
