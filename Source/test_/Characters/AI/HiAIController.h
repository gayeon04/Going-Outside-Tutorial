// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HiAIController.generated.h"

UCLASS()
class TEST__API AHiAIController : public AAIController
{
	GENERATED_BODY()

public:
	AHiAIController();

	virtual void OnPossess(APawn* NewPawn) override;
	virtual FVector GetFocalPointOnActor(const AActor* Actor) const override;

	
};
