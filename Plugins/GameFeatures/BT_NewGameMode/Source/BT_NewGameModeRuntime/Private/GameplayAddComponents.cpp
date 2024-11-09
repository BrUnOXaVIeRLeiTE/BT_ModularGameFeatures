#include "GameplayAddComponents.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameFeaturesSubsystemSettings.h"
#include "ScenarioInstanceSubsystem.h"

void UGameplayAddComponents::OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	UGameInstance* GameInstance = ScenarioSubsystem->GetGameInstance();

	if (!IsValid(GameInstance))
	{
		return;
	}

	if (UGameFrameworkComponentManager* GFCM = GameInstance->GetSubsystem<UGameFrameworkComponentManager>())
	{
		bool bIsServer = IsRunningDedicatedServer();
#if WITH_EDITOR
		checkSlow(GameInstance->GetWorldContext());
		bIsServer |= GameInstance->GetWorldContext()->RunAsDedicated;
#endif

		const bool bIsClient = !bIsServer;

		for (const FGameFeatureComponentEntry& Entry : ComponentList)
		{
			const bool bShouldAddRequest = (bIsServer && Entry.bServerComponent) || (bIsClient && Entry.bClientComponent);
			if (bShouldAddRequest)
			{
				if (!Entry.ActorClass.IsNull())
				{
					TSubclassOf<UActorComponent> ComponentClass = Entry.ComponentClass.LoadSynchronous();
					if (ComponentClass)
					{
						ComponentRequestHandles.Add(GFCM->AddComponentRequest(Entry.ActorClass, ComponentClass));
					}
					else if (!Entry.ComponentClass.IsNull())
					{
						UE_LOG(LogTemp, Error, TEXT("[GameFeatureData %s]: Failed to load component class %s. Not applying component."), *GetPathNameSafe(this), *Entry.ComponentClass.ToString());
					}
				}
			}
		}
	}
}

void UGameplayAddComponents::OnScenarioDeactivated(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown)
{
	ComponentRequestHandles.Empty();
}
