// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HiPlayerController.generated.h"

UCLASS()
class TEST__API AHiPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHiPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* IMC_Player = nullptr;
};
