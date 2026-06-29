// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HiInteractionComponent.generated.h"

class AHiPickupBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST__API UHiInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHiInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void AddInteractableObj(AHiPickupBase* NewPickupBase);
	
	UFUNCTION(BlueprintCallable)
	void RemoveInteractableObj(AHiPickupBase* PickupBaseToRemove);

	AHiPickupBase* GetFocusedInteractableObject();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
protected:
	TWeakObjectPtr<AHiPickupBase> CurrentPickupBase = nullptr;
	
	
	UPROPERTY()
	TArray<TWeakObjectPtr<AHiPickupBase>> Pickups;
};
