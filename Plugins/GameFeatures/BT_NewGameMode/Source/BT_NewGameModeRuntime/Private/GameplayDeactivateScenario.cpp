#include "GameplayDeactivateScenario.h"
#include "ScenarioInstanceSubsystem.h"
#include "GameplayScenario.h"

void UGameplayDeactivateScenario::OnScenarioActivated(UScenarioInstanceSubsystem* ScenarioSubsystem)
{
	for (int32 i = 0; i < ScenarioSubsystem->ActiveScenarios.Num(); i++)
	{
		UGameplayScenario* Scenario = ScenarioSubsystem->ActiveScenarios[i];

		if(IsValid(Scenario))
		{
			FGameplayTagContainer Tags;
			Scenario->GetOwnedGameplayTags(Tags);

			if (DeactivateScenarioQuery.Matches(Tags))
			{
				ScenarioSubsystem->DeactivateScenario(Scenario);
				i--;
			}
		}
	}
}
