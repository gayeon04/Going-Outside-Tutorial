// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/HiInteractionComponent.h"
#include "Interaction/HiPickupBase.h"


UHiInteractionComponent::UHiInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHiInteractionComponent::AddInteractableObj(AHiPickupBase* NewPickupBase)
{
	Pickups.AddUnique(NewPickupBase);
}

void UHiInteractionComponent::RemoveInteractableObj(AHiPickupBase* PickupBaseToRemove)
{
	Pickups.Remove(PickupBaseToRemove);
}

AHiPickupBase* UHiInteractionComponent::GetFocusedInteractableObject()
{
	if (CurrentPickupBase.IsValid() && CurrentPickupBase->CanInteract())
	{
		return CurrentPickupBase.Get();
	}

	return nullptr;
}

void UHiInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//update the most valuable target depending on the dist between it and the local pawn.
	float MinDist = FLT_MAX;
	const FVector OwnerLocation = GetOwner()->GetActorLocation();
	for (auto It = Pickups.CreateIterator(); It; ++It)
	{
		TWeakObjectPtr<AHiPickupBase> PickupBase = *It;
		if (!PickupBase.IsValid())
		{
			It.RemoveCurrent();
			continue;
		}
		const FVector PickupLocation = PickupBase->GetActorLocation();
		const float DistSqr = FVector::DistSquared(OwnerLocation, PickupLocation);

		if (DistSqr < MinDist)
		{
			CurrentPickupBase = PickupBase;
		}
	}
}
