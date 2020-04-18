//====================================================================//
// Copyright 2020 Elhoussine Mehnik (Mhousse1247). All Rights Reserved.
//==================== http://ue4resources.com/ =====================//

#include "OrientedCapsuleEditorStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "SlateOptMacros.h"	
#include "Styling/SlateTypes.h"
#include "EditorStyleSet.h"
#include "Styling/SlateStyle.h"
#include "Framework/Application/SlateApplication.h"


#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FOrientedCapsuleEditorStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )


FString FOrientedCapsuleEditorStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString IconsDir = IPluginManager::Get().FindPlugin(TEXT("OrientedCapsule"))->GetContentDir() / TEXT("Icons");
	return (IconsDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FOrientedCapsuleEditorStyle::StyleSet = NULL;
TSharedPtr< class ISlateStyle > FOrientedCapsuleEditorStyle::Get() { return StyleSet; }


FName FOrientedCapsuleEditorStyle::GetStyleSetName()
{
	return StyleSet->GetStyleSetName();
}


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FOrientedCapsuleEditorStyle::Initialize()
{

	// Const icon & thumbnail sizes
	const FVector2D Icon16x16(16.0f, 16.f);
	const FVector2D Icon128x128(128.f, 128.f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	// Style Set Allocation
	StyleSet = MakeShareable(new FSlateStyleSet("OrientedCapsuleEditorStyle"));
	FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("OrientedCapsule"))->GetContentDir();
	StyleSet->SetContentRoot(ContentDir);

	// Class Thumbnails
	StyleSet->Set("ClassIcon.OrientedCapsuleComponent", new IMAGE_BRUSH("icon_Capsule_40x", Icon16x16));

	// Register Style Set
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_BRUSH


void FOrientedCapsuleEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

