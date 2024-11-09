#include "BT_NewGameModeRuntimeModule.h"
#include "EngineMinimal.h"

#define LOCTEXT_NAMESPACE "FBT_NewGameModeRuntimeModule"

void FBT_NewGameModeRuntimeModule::StartupModule()
{
}

void FBT_NewGameModeRuntimeModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBT_NewGameModeRuntimeModule, BT_NewGameModeRuntime)
