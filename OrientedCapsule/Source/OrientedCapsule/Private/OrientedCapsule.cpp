//====================================================================//
// Copyright 2020 Elhoussine Mehnik (Mhousse1247). All Rights Reserved.
//==================== http://ue4resources.com/ =====================//

#include "OrientedCapsule.h"

#define LOCTEXT_NAMESPACE "FOrientedCapsuleModule"

void FOrientedCapsuleModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FOrientedCapsuleModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOrientedCapsuleModule, OrientedCapsule)