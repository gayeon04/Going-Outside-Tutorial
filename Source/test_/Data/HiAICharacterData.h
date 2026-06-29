// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "HiAICharacterData.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class TEST__API UHiCharacterStartData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	bool IsValid() const
	{
		return BT != nullptr && VisibleMesh != nullptr && GaitTag.IsValid();
	}
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> BT = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(Categories="Als.Gait"))
	FGameplayTag GaitTag =  FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> VisibleMesh = nullptr;
};

UCLASS()
class TEST__API UHiAICharacterData : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Hi|BT")
	UHiCharacterStartData* GetRandomCharacterData()
	{
		TArray<UHiCharacterStartData*> CharacterDataArray;
		CharacterDataMap.GenerateValueArray(CharacterDataArray);

		const int32 RandomIdx = FMath::RandRange(0, CharacterDataArray.Num() - 1);
		return CharacterDataArray[RandomIdx]; // [ 0 ~ CharacterDataArray.Num()-1 
	}
	
	UFUNCTION(BlueprintCallable, Category="Hi|BT")
	UHiCharacterStartData* GetStartDataByTag(const FGameplayTag Tag)
	{
		return CharacterDataMap.Contains(Tag) ? *CharacterDataMap.Find(Tag) : nullptr; 
	}

public:
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, UHiCharacterStartData*> CharacterDataMap;
};
