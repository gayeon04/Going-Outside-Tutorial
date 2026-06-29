// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HiCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "HiAICharacter.generated.h"

class UBehaviorTree;
class AAIController;

UCLASS()
class TEST__API AHiAICharacter : public AHiCharacter
{
	GENERATED_BODY()

public:
	AHiAICharacter();

	UFUNCTION(BlueprintCallable)
	AAIController* GetAIController() const;

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnSeePawn(APawn* SeenPawn);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="HikingGame")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI|Sensing")
	TObjectPtr<UPawnSensingComponent> PawnSensingComp = nullptr;
};
