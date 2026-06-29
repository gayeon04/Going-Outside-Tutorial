// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "HiDevSettings.generated.h"

// 이 클래스는 더 이상 사용되지 않습니다. HiAISpawner가 AICharacterData를 직접 보유합니다.
UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Hi Dev Settings"))
class TEST__API UHiDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
};
