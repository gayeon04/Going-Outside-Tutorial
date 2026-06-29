// Fill out your copyright notice in the Description page of Project Settings.


#include "HiAIController.h"


AHiAIController::AHiAIController()
{
	
}

void AHiAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
}

FVector AHiAIController::GetFocalPointOnActor(const AActor* Actor) const
{
	const auto* FocusedPawn{Cast<APawn>(Actor)};
	if (IsValid(FocusedPawn))
	{
		return FocusedPawn->GetPawnViewLocation();
	}

	return Super::GetFocalPointOnActor(Actor);
}
