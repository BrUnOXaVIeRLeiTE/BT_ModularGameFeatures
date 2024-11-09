// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "FirstPersonAssetManager.generated.h"

UCLASS()
class FIRSTPERSON_API UFirstPersonAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;
};
