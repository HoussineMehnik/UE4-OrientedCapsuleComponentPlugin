// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "OrientedCapsule/Public/OrientedCapsuleComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOrientedCapsuleComponent() {}
// Cross Module References
	ORIENTEDCAPSULE_API UClass* Z_Construct_UClass_UOrientedCapsuleComponent_NoRegister();
	ORIENTEDCAPSULE_API UClass* Z_Construct_UClass_UOrientedCapsuleComponent();
	ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent();
	UPackage* Z_Construct_UPackage__Script_OrientedCapsule();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
// End Cross Module References
	void UOrientedCapsuleComponent::StaticRegisterNativesUOrientedCapsuleComponent()
	{
	}
	UClass* Z_Construct_UClass_UOrientedCapsuleComponent_NoRegister()
	{
		return UOrientedCapsuleComponent::StaticClass();
	}
	struct Z_Construct_UClass_UOrientedCapsuleComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_CapsuleRotation_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_CapsuleRotation;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UOrientedCapsuleComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UCapsuleComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_OrientedCapsule,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOrientedCapsuleComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Collision" },
		{ "DisplayName", "Oriented Capsule Collision" },
		{ "HideCategories", "Object LOD Lighting TextureStreaming Object LOD Lighting TextureStreaming Object LOD Lighting TextureStreaming Activation Components|Activation Trigger VirtualTexture" },
		{ "IncludePath", "OrientedCapsuleComponent.h" },
		{ "ModuleRelativePath", "Public/OrientedCapsuleComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOrientedCapsuleComponent_Statics::NewProp_CapsuleRotation_MetaData[] = {
		{ "Category", "Shape" },
		{ "ModuleRelativePath", "Public/OrientedCapsuleComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UOrientedCapsuleComponent_Statics::NewProp_CapsuleRotation = { "CapsuleRotation", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UOrientedCapsuleComponent, CapsuleRotation), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(Z_Construct_UClass_UOrientedCapsuleComponent_Statics::NewProp_CapsuleRotation_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UOrientedCapsuleComponent_Statics::NewProp_CapsuleRotation_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOrientedCapsuleComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOrientedCapsuleComponent_Statics::NewProp_CapsuleRotation,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UOrientedCapsuleComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOrientedCapsuleComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UOrientedCapsuleComponent_Statics::ClassParams = {
		&UOrientedCapsuleComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UOrientedCapsuleComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UOrientedCapsuleComponent_Statics::PropPointers),
		0,
		0x00B010A4u,
		METADATA_PARAMS(Z_Construct_UClass_UOrientedCapsuleComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UOrientedCapsuleComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UOrientedCapsuleComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UOrientedCapsuleComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UOrientedCapsuleComponent, 1901454992);
	template<> ORIENTEDCAPSULE_API UClass* StaticClass<UOrientedCapsuleComponent>()
	{
		return UOrientedCapsuleComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UOrientedCapsuleComponent(Z_Construct_UClass_UOrientedCapsuleComponent, &UOrientedCapsuleComponent::StaticClass, TEXT("/Script/OrientedCapsule"), TEXT("UOrientedCapsuleComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UOrientedCapsuleComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
