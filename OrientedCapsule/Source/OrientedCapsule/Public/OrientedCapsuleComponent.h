//====================================================================//
// Copyright 2020 Elhoussine Mehnik (Mhousse1247). All Rights Reserved.
//==================== http://ue4resources.com/ =====================//

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/CapsuleComponent.h"
#include "OrientedCapsuleComponent.generated.h"

class FPrimitiveSceneProxy;

UCLASS(ClassGroup = "Collision", editinlinenew, hidecategories = (Object, LOD, Lighting, TextureStreaming), meta = (DisplayName = "Oriented Capsule Collision", BlueprintSpawnableComponent))
class ORIENTEDCAPSULE_API UOrientedCapsuleComponent : public UCapsuleComponent
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shape)
		FRotator CapsuleRotation;

private:
	void AddCapsuleShapeToGeomArray();
	void SetCapsuleShapeToNewGeom(const FPhysicsShapeHandle& Shape);
	void CreateCapsuleShapeBodySetupIfNeeded();

public:

	virtual void UpdateBodySetup() override;
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};