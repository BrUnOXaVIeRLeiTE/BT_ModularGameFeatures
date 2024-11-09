#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "GameplayEffect.h"
#include "Engine/AssetManager.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameplayScenarioFunctionLibrary.generated.h"

UCLASS()
class BT_NEWGAMEMODERUNTIME_API UGameplayScenarioFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Assets")
	static bool GetAssetTagAsString(FPrimaryAssetId Asset, FName Tag, FString& OutString);

	UFUNCTION(BlueprintPure, Category = "Assets")
	static bool GetAssetTagAsText(FPrimaryAssetId Asset, FName Tag, FText& OutText);

	UFUNCTION(BlueprintPure, Category = "Assets")
	static bool GetAssetTagAsBool(FPrimaryAssetId Asset, FName Tag, bool& OutBool);
};
