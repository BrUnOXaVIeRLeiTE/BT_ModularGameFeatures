#include "BT_NewGameMechComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

UJetpackComponent::UJetpackComponent()
	: Super()
{
	if (!GetOuter()->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> InputActionFinder(TEXT("Script/Engine.UInputAction'/BT_NewGameMech/IA_Jetpack.IA_Jetpack'"));
		if (InputActionFinder.Succeeded())
		{
			JetpackMoveAction = InputActionFinder.Object;
		}
	}
}

void UJetpackComponent::PostLoad()
{
	Super::PostLoad();

	if (GetWorld() && !GetWorld()->IsGameWorld())
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("DeactivateGameFeaturePlugin BT_NewGameMech"), nullptr);
	}
}

void UJetpackComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() && JetpackMoveAction.IsValid())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent =
				Cast<UEnhancedInputComponent>(GetOwner()->GetComponentByClass(UEnhancedInputComponent::StaticClass())))
		{
			// Add Jetpack Moving Controls
			// EnhancedInputComponent->BindAction(JetpackMoveAction.Get(), ETriggerEvent::Triggered, this, &UJetpackComponent::JetpackMove);
		}
	}
}

void UJetpackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	JetpackMoveAction = nullptr;

	if (GetOwner())
	{
		if (UEnhancedInputComponent* EnhancedInputComponent =
				Cast<UEnhancedInputComponent>(GetOwner()->GetComponentByClass(UEnhancedInputComponent::StaticClass())))
		{
			// Remove Jetpack Moving Controls
			EnhancedInputComponent->ClearBindingsForObject(this);
		}
	}

	Super::EndPlay(EndPlayReason);
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("DeactivateGameFeaturePlugin BT_CoinGame"), nullptr);
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("DeactivateGameFeaturePlugin BT_NewGameMech"), nullptr);
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("DeactivateGameFeaturePlugin BT_PlayerAbilities"), nullptr);
}

void UJetpackComponent::JetpackMove(const FInputActionValue& Value)
{
	/// This is one way of having this done, however,
	/// I will go a bit further and do it the 'GAS' way with modular ability system.
}
