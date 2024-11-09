#include "GameplayScenarioFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

bool UGameplayScenarioFunctionLibrary::GetAssetTagAsString(FPrimaryAssetId Asset, FName Tag, FString& OutString)
{
	UAssetManager& LocalManager = UAssetManager::Get();
	FAssetData	   AssetData;

	if (!LocalManager.GetPrimaryAssetData(Asset, AssetData))
	{
		return false;
	}

	bool bFound = AssetData.GetTagValue<FString>(Tag, OutString);
	return bFound;
}

bool UGameplayScenarioFunctionLibrary::GetAssetTagAsText(FPrimaryAssetId Asset, FName Tag, FText& OutText)
{
	UAssetManager& LocalManager = UAssetManager::Get();
	FAssetData	   AssetData;

	if (!LocalManager.GetPrimaryAssetData(Asset, AssetData))
	{
		return false;
	}

	bool bFound = AssetData.GetTagValue<FText>(Tag, OutText);
	return bFound;
}

bool UGameplayScenarioFunctionLibrary::GetAssetTagAsBool(FPrimaryAssetId Asset, FName Tag, bool& OutBool)
{
	UAssetManager& LocalManager = UAssetManager::Get();
	FAssetData	   AssetData;

	if (!LocalManager.GetPrimaryAssetData(Asset, AssetData))
	{
		return false;
	}

	bool bFound = AssetData.GetTagValue<bool>(Tag, OutBool);
	return bFound;
}
