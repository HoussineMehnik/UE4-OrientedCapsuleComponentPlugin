//====================================================================//
// Copyright 2020 Elhoussine Mehnik (Mhousse1247). All Rights Reserved.
//==================== http://ue4resources.com/ =====================//

#include "OrientedCapsuleEditor.h"
#include "OrientedCapsuleEditorStyle.h"

#define LOCTEXT_NAMESPACE "FOrientedCapsuleEditorModule"

void FOrientedCapsuleEditorModule::StartupModule()
{
	FOrientedCapsuleEditorStyle::Initialize();
}

void FOrientedCapsuleEditorModule::ShutdownModule()
{
	FOrientedCapsuleEditorStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOrientedCapsuleEditorModule, OrientedCapsuleEditor)