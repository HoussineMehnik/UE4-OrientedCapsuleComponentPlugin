//====================================================================//
// Copyright 2020 Elhoussine Mehnik (Mhousse1247). All Rights Reserved.
//==================== http://ue4resources.com/ =====================//


#include "OrientedCapsuleComponent.h"
#include "WorldCollision.h"
#include "PrimitiveViewRelevance.h"
#include "PrimitiveSceneProxy.h"
#include "SceneManagement.h"
#include "PhysicsEngine/SphylElem.h"
#include "PhysicsEngine/BodySetup.h"
#include "PhysicsEngine/BoxElem.h"
#include "PhysicsEngine/SphereElem.h"






#if WITH_PHYSX
#include "PhysXPublic.h"
#endif // WITH_PHYSX

UOrientedCapsuleComponent::UOrientedCapsuleComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CapsuleRotation(ForceInitToZero)
{

}


template <EShapeBodySetupHelper UpdateBodySetupAction>
bool InvalidateOrUpdateCapsuleBodySetup1(UBodySetup*& ShapeBodySetup, bool bUseArchetypeBodySetup, float CapsuleRadius, float CapsuleHalfHeight, const FRotator& CapsuleRotation)
{
	check((bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::InvalidateSharingIfStale) || (!bUseArchetypeBodySetup && UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup));
	check(ShapeBodySetup->AggGeom.SphylElems.Num() == 1);
	FKSphylElem* SE = ShapeBodySetup->AggGeom.SphylElems.GetData();

	const float Length = 2 * FMath::Max(CapsuleHalfHeight - CapsuleRadius, 0.f);	//SphylElem uses height from center of capsule spheres, but UCapsuleComponent uses halfHeight from end of the sphere

	if (UpdateBodySetupAction == EShapeBodySetupHelper::UpdateBodySetup)
	{
		SE->SetTransform(FTransform(CapsuleRotation));
		SE->Radius = CapsuleRadius;
		SE->Length = Length;
	}
	else
	{
		if (SE->Radius != CapsuleRadius || SE->Length != Length || !SE->Rotation.Equals(CapsuleRotation))
		{
			ShapeBodySetup = nullptr;
			bUseArchetypeBodySetup = false;
		}
	}

	return bUseArchetypeBodySetup;
}



void UOrientedCapsuleComponent::AddCapsuleShapeToGeomArray()
{
	ShapeBodySetup->AggGeom.SphylElems.Add(FKSphylElem());
}

#if WITH_PHYSX
void UOrientedCapsuleComponent::SetCapsuleShapeToNewGeom(const FPhysicsShapeHandle& Shape)
{
	FPhysicsInterface::SetUserData(Shape, (void*)ShapeBodySetup->AggGeom.SphylElems[0].GetUserData());
}
#endif

void UOrientedCapsuleComponent::CreateCapsuleShapeBodySetupIfNeeded()
{
	if (ShapeBodySetup == nullptr || ShapeBodySetup->IsPendingKill())
	{
		ShapeBodySetup = NewObject<UBodySetup>(this, NAME_None, RF_Transient);
		if (GUObjectArray.IsDisregardForGC(this))
		{
			ShapeBodySetup->AddToRoot();
		}

		// If this component is in GC cluster, make sure we add the body setup to it to
		ShapeBodySetup->AddToCluster(this);
		// if we got created outside of game thread, but got added to a cluster, 
		// we no longer need the Async flag
		if (ShapeBodySetup->HasAnyInternalFlags(EInternalObjectFlags::Async) && GUObjectClusters.GetObjectCluster(ShapeBodySetup))
		{
			ShapeBodySetup->ClearInternalFlags(EInternalObjectFlags::Async);
		}

		ShapeBodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
		AddCapsuleShapeToGeomArray();
		ShapeBodySetup->bNeverNeedsCookedCollisionData = true;
		bUseArchetypeBodySetup = false;	//We're making our own body setup, so don't use the archetype's.

		//Update bodyinstance and shapes
		BodyInstance.BodySetup = ShapeBodySetup;
		{
			if (BodyInstance.IsValidBodyInstance())
			{
#if WITH_PHYSX
				FPhysicsCommand::ExecuteWrite(BodyInstance.GetActorReferenceWithWelding(), [this](const FPhysicsActorHandle& Actor)
				{
					TArray<FPhysicsShapeHandle> Shapes;
					BodyInstance.GetAllShapes_AssumesLocked(Shapes);

					for (FPhysicsShapeHandle& Shape : Shapes)	//The reason we iterate is we may have multiple scenes and thus multiple shapes, but they are all pointing to the same geometry
					{
						//Update shape with the new body setup. Make sure to only update shapes owned by this body instance
						if (BodyInstance.IsShapeBoundToBody(Shape))
						{
							SetCapsuleShapeToNewGeom(Shape);
						}
					}
				});
#endif
			}
		}
	}
}


void UOrientedCapsuleComponent::UpdateBodySetup()
{
	if (PrepareSharedBodySetup<UOrientedCapsuleComponent>())
	{
		bUseArchetypeBodySetup = InvalidateOrUpdateCapsuleBodySetup1<EShapeBodySetupHelper::InvalidateSharingIfStale>(ShapeBodySetup, bUseArchetypeBodySetup, CapsuleRadius, CapsuleHalfHeight, CapsuleRotation);
	}

	CreateCapsuleShapeBodySetupIfNeeded();

	if (!bUseArchetypeBodySetup)
	{
		InvalidateOrUpdateCapsuleBodySetup1<EShapeBodySetupHelper::UpdateBodySetup>(ShapeBodySetup, bUseArchetypeBodySetup, CapsuleRadius, CapsuleHalfHeight, CapsuleRotation);
	}
}



FPrimitiveSceneProxy* UOrientedCapsuleComponent::CreateSceneProxy()
{
	/** Represents a UCapsuleComponent to the scene manager. */
	class FDrawCylinderSceneProxy final : public FPrimitiveSceneProxy
	{
	public:
		SIZE_T GetTypeHash() const override
		{
			static size_t UniquePointer;
			return reinterpret_cast<size_t>(&UniquePointer);
		}

		FDrawCylinderSceneProxy(const UOrientedCapsuleComponent* InComponent)
			: FPrimitiveSceneProxy(InComponent)
			, bDrawOnlyIfSelected(InComponent->bDrawOnlyIfSelected)
			, CapsuleRadius(InComponent->CapsuleRadius)
			, CapsuleHalfHeight(InComponent->CapsuleHalfHeight)
			, ShapeColor(InComponent->ShapeColor)
			, Rotation(InComponent->CapsuleRotation)
		{
			bWillEverBeLit = false;
		}

		virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
		{
			QUICK_SCOPE_CYCLE_COUNTER(STAT_GetDynamicMeshElements_DrawDynamicElements);


			const FMatrix& LocalToWorld = GetLocalToWorld();
			const int32 CapsuleSides = FMath::Clamp<int32>(CapsuleRadius / 4.f, 16, 64);


			for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
			{

				if (VisibilityMap & (1 << ViewIndex))
				{
					const FSceneView* View = Views[ViewIndex];
					const FLinearColor DrawCapsuleColor = GetViewSelectionColor(ShapeColor, *View, IsSelected(), IsHovered(), false, IsIndividuallySelected());

					FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
					DrawWireCapsule(PDI, LocalToWorld.GetOrigin(), 
						LocalToWorld.TransformVector(FRotationMatrix(Rotation).GetScaledAxis(EAxis::X)),
						LocalToWorld.TransformVector(FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y)),
						LocalToWorld.TransformVector(FRotationMatrix(Rotation).GetScaledAxis(EAxis::Z)),
						DrawCapsuleColor, CapsuleRadius, CapsuleHalfHeight, CapsuleSides, SDPG_World);
				}
			}
		}

		virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
		{
			const bool bProxyVisible = !bDrawOnlyIfSelected || IsSelected();

			// Should we draw this because collision drawing is enabled, and we have collision
			const bool bShowForCollision = View->Family->EngineShowFlags.Collision && IsCollisionEnabled();

			FPrimitiveViewRelevance Result;
			Result.bDrawRelevance = (IsShown(View) && bProxyVisible) || bShowForCollision;
			Result.bDynamicRelevance = true;
			Result.bShadowRelevance = IsShadowCast(View);
			Result.bEditorPrimitiveRelevance = UseEditorCompositing(View);
			return Result;
		}
		virtual uint32 GetMemoryFootprint(void) const override { return(sizeof(*this) + GetAllocatedSize()); }
		uint32 GetAllocatedSize(void) const { return(FPrimitiveSceneProxy::GetAllocatedSize()); }

	private:
		const uint32	bDrawOnlyIfSelected : 1;
		const float		CapsuleRadius;
		const float		CapsuleHalfHeight;
		const FColor	ShapeColor;
		const FRotator	Rotation;
	};

	return new FDrawCylinderSceneProxy(this);
}
