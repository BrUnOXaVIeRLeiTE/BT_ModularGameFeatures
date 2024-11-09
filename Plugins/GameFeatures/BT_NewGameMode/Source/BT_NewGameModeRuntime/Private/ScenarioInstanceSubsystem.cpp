#include "ScenarioInstanceSubsystem.h"
#include "Engine.h"

#include "GameplayScenario.h"
#include "GameplayScenarioAction.h"

#include "Engine/AssetManager.h"
#include "Engine/AssetManagerTypes.h"
#include "Engine/LevelStreamingDynamic.h"

#include "GameFeatureAction.h"
#include "GameFeaturesSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameplayScenario, Log, All);

UScenarioInstanceSubsystem::UScenarioInstanceSubsystem()
	: Super()
{
	bBecomeListenServerFromStandalone = true;
	MapTransitionScenario = nullptr;
}

void UScenarioInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("StartScenario"),
		TEXT("Begin a Scenario, Changing maps if needed"),
		FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateLambda([this](const TArray<FString>& Args, UWorld* World, FOutputDevice& Ar) {
			if (Args.Num() != 1)
			{
				Ar.Logf(TEXT("Error loading Scenario: Expected one parameter to StartScenario"));
				return;
			}

			// Parse the primary asset id
			FPrimaryAssetId ScenarioAsset = FPrimaryAssetId::FromString(Args[0]);

			if (!ScenarioAsset.IsValid())
			{
				FString AssetId = (ScenarioAsset.ToString().IsEmpty()) ? TEXT("NONE") : ScenarioAsset.ToString();
				Ar.Logf(TEXT("Error loading Scenario (%s): Asset Id Is Not Valid"), *AssetId);
				return;
			}
			UAssetManager& Manager = UAssetManager::Get();

			FSoftObjectPath Path = Manager.GetPrimaryAssetPath(ScenarioAsset);

			if (!Path.IsValid())
			{
				Ar.Logf(TEXT("Error loading Scenario (%s): Scenario does not exist"), *ScenarioAsset.ToString());
				return;
			}

			auto Handle = Manager.LoadPrimaryAsset(ScenarioAsset);

			if (Handle.IsValid())
			{
				Handle->WaitUntilComplete(10);
			}

			UGameplayScenario* Scenario = Manager.GetPrimaryAssetObject<UGameplayScenario>(ScenarioAsset);

			UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: Going to Scenario %s"), *GetNameSafe(Scenario));

			SetPendingScenario(Scenario);
			TransitionToPendingScenario(true);
		}),
		ECVF_Default);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnPostLoadMap);
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
}

void UScenarioInstanceSubsystem::SetPendingScenario(UGameplayScenario* Scenairo)
{
	PendingScenario = Scenairo;
}

void UScenarioInstanceSubsystem::TransitionToPendingScenario(bool bForce)
{
	if (!IsValid(PendingScenario))
	{
		UE_LOG(LogGameplayScenario, Warning, TEXT("ScenarioSubsystem: TransitionToPendingScenario called with no pending scenario"));
		return;
	}

	UGameplayScenario* Scenario = PendingScenario;
	PendingScenario = nullptr;

	StartActivatingScenario(Scenario, bForce);
}

void UScenarioInstanceSubsystem::PreActivateScenario(FPrimaryAssetId ScenarioAsset, bool bForce)
{
	UAssetManager& Manager = UAssetManager::Get();

	FSoftObjectPath Path = Manager.GetPrimaryAssetPath(ScenarioAsset);

	if (!ensure(Path.IsValid()))
	{
		return;
	}

	UGameplayScenario* Scenario = Manager.GetPrimaryAssetObject<UGameplayScenario>(ScenarioAsset);

	if (!IsValid(Scenario))
	{
		auto LoadHandle = Manager.LoadPrimaryAsset(ScenarioAsset);
		if (LoadHandle.IsValid())
		{
			LoadHandle->WaitUntilComplete();
		}

		Scenario = Manager.GetPrimaryAssetObject<UGameplayScenario>(ScenarioAsset);
	}

	if (IsValid(Scenario))
	{
		PreActivateScenario(Scenario, bForce);
	}
}

void UScenarioInstanceSubsystem::PreActivateScenario(UGameplayScenario* Scenario, bool bForce)
{
	if (!IsValid(Scenario))
	{
		return;
	}
	if (!bForce && IsScenarioActive(Scenario))
	{
		return;
	}

	UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: PreActivating Scenario %s"), *GetNameSafe(Scenario));

	Scenario->PreActivateScenario(this);
}

void UScenarioInstanceSubsystem::ActivateScenario(UGameplayScenario* Scenario, bool bForce)
{
	if (!IsValid(Scenario))
	{
		return;
	}
	if (!bForce && IsScenarioActive(Scenario))
	{
		return;
	}

	UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: Activating Scenario %s"), *GetNameSafe(Scenario));

	ActiveScenarios.Add(Scenario);

	for (UGameplayScenarioAction* Action : Scenario->ScenarioActions)
	{
		Action->OnScenarioActivated(this);
	}
	OnScenarioActivated.Broadcast(Scenario);
}

void UScenarioInstanceSubsystem::ActivateScenario(FPrimaryAssetId ScenarioAsset, bool bForce)
{
	UAssetManager& Manager = UAssetManager::Get();

	FSoftObjectPath Path = Manager.GetPrimaryAssetPath(ScenarioAsset);

	if (!ensure(Path.IsValid()))
	{
		return;
	}

	UGameplayScenario* Scenario = Manager.GetPrimaryAssetObject<UGameplayScenario>(ScenarioAsset);

	if (!IsValid(Scenario))
	{
		auto LoadHandle = Manager.LoadPrimaryAsset(ScenarioAsset);
		if (LoadHandle.IsValid())
		{
			LoadHandle->WaitUntilComplete();
		}

		Scenario = Manager.GetPrimaryAssetObject<UGameplayScenario>(ScenarioAsset);
	}

	if (IsValid(Scenario))
	{
		ActivateScenario(Scenario, bForce);
	}
}

void UScenarioInstanceSubsystem::DeactivateScenario(UGameplayScenario* Scenario)
{
	if (!IsScenarioActive(Scenario))
	{
		return;
	}

	UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: Deactivating Scenario %s"), *GetNameSafe(Scenario));

	Scenario->DeactivateScenario(this);

	ActiveScenarios.RemoveSwap(Scenario);

	OnScenarioDeactivated.Broadcast(Scenario);
}

void UScenarioInstanceSubsystem::DeactivateScenario(FPrimaryAssetId ScenarioAsset)
{
	UGameplayScenario** SearchedScenario = ActiveScenarios.FindByPredicate([ScenarioAsset](UGameplayScenario* Scenario) {
		if (Scenario->GetPrimaryAssetId() == ScenarioAsset)
		{
			return true;
		}
		return false;
	});

	if (SearchedScenario)
	{
		DeactivateScenario(*SearchedScenario);
	}
}

void UScenarioInstanceSubsystem::TearDownActiveScenarios()
{
	UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: Tearing Down all active scenarios"));
	for (UGameplayScenario* Scenario : ActiveScenarios)
	{
		if (IsValid(Scenario))
		{
			Scenario->DeactivateScenario(this, true);
			OnScenarioDeactivated.Broadcast(Scenario);
		}
	}
	ActiveScenarios.Empty();
}

bool UScenarioInstanceSubsystem::IsScenarioActive(UGameplayScenario* Scenario) const
{
	if (ActiveScenarios.Contains(Scenario))
	{
		return true;
	}

	return false;
}

void UScenarioInstanceSubsystem::OnPostLoadMap(UWorld* World)
{
	if (IsValid(MapTransitionScenario))
	{
		UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: After Map Load, Finishing Activating %s"), *GetNameSafe(PendingScenario));

		FinishActivatingScenario(MapTransitionScenario, true);
		MapTransitionScenario = nullptr;
	}

	if (IsValid(PendingScenario))
	{
		UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem: After Map Load, Transiting to pending Scenario %s"), *GetNameSafe(PendingScenario));

		TransitionToPendingScenario();
	}
}

void UScenarioInstanceSubsystem::OnPreLoadMap(const FString& MapName)
{
	TearDownActiveScenarios();
}
void UScenarioInstanceSubsystem::StartActivatingScenario(UGameplayScenario* Scenario, bool bForce)
{
	if (Scenario->Map.IsNull())
	{
		return;
	}
	Scenario->Map.LoadSynchronous();

	TearDownActiveScenarios();
	PreActivateScenario(Scenario, bForce);

	if (Scenario->Map.IsValid())
	{
		UE_LOG(LogGameplayScenario, Verbose, TEXT("ScenarioSubsystem:Transiting to world %s for scenario %s"), *Scenario->Map.ToString(), *GetNameSafe(Scenario));

		TransitionToWorld(Scenario->Map.Get());
		MapTransitionScenario = Scenario;
		return;
	}

	FinishActivatingScenario(Scenario, bForce);
}

void UScenarioInstanceSubsystem::FinishActivatingScenario(UGameplayScenario* Scenario, bool bForce)
{
	ActivateScenario(Scenario, bForce);
}

void UScenarioInstanceSubsystem::TransitionToWorld(TObjectPtr<UWorld> WorldAsset)
{
	const UWorld* const World = GetGameInstance()->GetWorld();

	const bool bIsClient = World->GetNetMode() == NM_Client;

	if (bIsClient)
	{
		return;
	}

	const bool bIsDedicatedServer = IsRunningDedicatedServer();
	const bool bIsListenServer = World->GetNetMode() == NM_ListenServer;
	const bool bIsStandalone = World->GetNetMode() == NM_Standalone;

	FURL NewMapURL = FURL(*WorldAsset->GetPrimaryAssetId().PrimaryAssetName.ToString());

	if (bIsStandalone || bIsListenServer)
	{
		NewMapURL.AddOption(TEXT("listen"));
	}

	if (AGameModeBase* GameMode = World->GetAuthGameMode())
	{
		if (GameMode->CanServerTravel(NewMapURL.ToString(), false))
		{
			GameMode->ProcessServerTravel(NewMapURL.ToString(), false);
		}
	}
}
