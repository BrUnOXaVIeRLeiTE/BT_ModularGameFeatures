#include "GameplayScenario.h"
#include "GameplayScenarioAction.h"
#include "ScenarioInstanceSubsystem.h"

UGameplayScenario::UGameplayScenario()
	: Super()
{

}

void UGameplayScenario::PreActivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	ForEachAction_Mutable([&ScenarioSubsystem](UGameplayScenarioAction* Action)
	{
		Action->OnScenarioPreActivated(ScenarioSubsystem);
	});	
}

void UGameplayScenario::ActivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	ForEachAction_Mutable([&ScenarioSubsystem](UGameplayScenarioAction* Action)
	{
		Action->OnScenarioActivated(ScenarioSubsystem);
	});
}

void UGameplayScenario::DeactivateScenario(UScenarioInstanceSubsystem* ScenarioSubsystem, bool bTearDown)
{
	ForEachAction_Mutable([&ScenarioSubsystem](UGameplayScenarioAction* Action)
	{
		Action->OnScenarioDeactivated(ScenarioSubsystem);
	});
}

void UGameplayScenario::ForEachAction_Mutable(Predicate Predicate)
{
	for (UGameplayScenarioAction* Action : ScenarioActions)
	{
		if(IsValid(Action))
		{
			Predicate(Action);
		}
	}
}

void UGameplayScenario::ForEachAction(ConstPredicate Predicate) const
{
	for (UGameplayScenarioAction* Action : ScenarioActions)
	{
		if (IsValid(Action))
		{
			Predicate(Action);
		}
	}
}
