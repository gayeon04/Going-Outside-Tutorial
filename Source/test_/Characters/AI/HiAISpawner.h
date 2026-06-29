// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "HiAISpawner.generated.h"

class UBoxComponent;
class AHiAICharacter;
class UHiAICharacterData;

UCLASS(Blueprintable, BlueprintType)
class TEST__API AHiAISpawner : public AActor
{
	GENERATED_BODY()

public:
	AHiAISpawner(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	FVector GetRandomPointInRange() const;

protected:
	UPROPERTY()
	TObjectPtr<UBoxComponent> BoxComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer StartupCharacterTags;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AHiAICharacter> AICharClass = nullptr;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UHiAICharacterData> AICharacterData = nullptr;
};
