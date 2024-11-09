#include "GameplayStreamLevelInstance.h"

#include "Engine/AssetManager.h"
#include "Engine/AssetManagerTypes.h"
#include "Engine/LevelStreamingDynamic.h"

#include "ScenarioInstanceSubsystem.h"

void UGameplayStreamLevelInstance::OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	UAssetManager& AssetManager = UAssetManager::Get();
	for (FPrimaryAssetId AssetId : StreamedInLevels)
	{
		FSoftObjectPath ObjPath = AssetManager.GetPrimaryAssetPath(AssetId);
		if (ObjPath.IsValid())
		{
			TSoftObjectPtr<UWorld> ObjPtr(ObjPath);

			bool bSuccess = false;
			ULevelStreamingDynamic* Streamer = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(ScenarioSubsystem->GetGameInstance(), ObjPtr, FVector::ZeroVector, FRotator::ZeroRotator, bSuccess);

			if (bSuccess)
			{
				Streamer->SetShouldBeLoaded(true);
				DynamicLevelStreams.AddUnique(Streamer);
			}
		}
	}
}

void UGameplayStreamLevelInstance::OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown)
{
	if (bTearDown)
	{
		return;
	}
	for (ULevelStreamingDynamic* LevelStream : DynamicLevelStreams)
	{
		LevelStream->SetIsRequestingUnloadAndRemoval(true);
	}
}
