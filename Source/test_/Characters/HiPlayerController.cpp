// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/HiPlayerController.h"

AHiPlayerController::AHiPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AHiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (auto* LP = GetLocalPlayer())
		if (auto* Sub = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
			Sub->AddMappingContext(IMC_Player, 0);
}

void AHiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AHiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}
