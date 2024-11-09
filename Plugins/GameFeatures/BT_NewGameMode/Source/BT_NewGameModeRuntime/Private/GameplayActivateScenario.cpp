#include "GameplayActivateScenario.h"
#include "Engine/AssetManager.h"
#include "Engine/AssetManagerTypes.h"

#include "GameplayScenario.h"
#include "ScenarioInstanceSubsystem.h"

void UGameplayActivateScenario::OnScenarioPreActivated(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	for (FPrimaryAssetId ScenarioAsset : Scenarios)
	{
		ScenarioSubsystem->PreActivateScenario(ScenarioAsset, false);
	}
}

void UGameplayActivateScenario::OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem)
{	
	for (FPrimaryAssetId ScenarioAsset : Scenarios)
	{		
		ScenarioSubsystem->ActivateScenario(ScenarioAsset, false);
	}
}

void UGameplayActivateScenario::OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown)
{
	if (bTearDown)
	{
		return;
	}
	for (FPrimaryAssetId ScenarioAsset : Scenarios)
	{
		ScenarioSubsystem->DeactivateScenario(ScenarioAsset);
	}
}
