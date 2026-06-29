// Fill out your copyright notice in the Description page of Project Settings.

#include "HiAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AHiAICharacter::AHiAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensingComp->SightRadius = 500.f;
	PawnSensingComp->SetPeripheralVisionAngle(60.f);
}

AAIController* AHiAICharacter::GetAIController() const
{
	return Cast<AAIController>(GetController());
}

void AHiAICharacter::BeginPlay()
{
	Super::BeginPlay();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHiAICharacter::OnSeePawn);

	if (BehaviorTree)
	{
		if (AAIController* AIController = GetAIController())
		{
			AIController->RunBehaviorTree(BehaviorTree);
		}
	}
}

void AHiAICharacter::OnSeePawn(APawn* SeenPawn)
{
	if (!SeenPawn || !SeenPawn->IsPlayerControlled())
		return;

	if (AAIController* AIC = GetAIController())
	{
		if (UBlackboardComponent* BB = AIC->GetBlackboardComponent())
		{
			BB->SetValueAsObject(FName("PlayerPawn"), SeenPawn);
		}
	}
}
