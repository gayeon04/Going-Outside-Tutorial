#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "StatEffectMessage.generated.h"

UENUM(BlueprintType)
enum class EStatEffectType : uint8
{
	None        UMETA(DisplayName="None"),
	HealthDelta UMETA(DisplayName="HealthDelta"),   // 체력 변화(기본)
	StaminaDelta UMETA(DisplayName="StaminaDelta"), // 나중 확장용
	MentalDelta  UMETA(DisplayName="MentalDelta"),  // 나중 확장용
	MoveSpeedMul UMETA(DisplayName="MoveSpeedMul"), // 나중 확장용
	UIMessage    UMETA(DisplayName="UIMessage"),    // 텍스트만 띄우는 타입(원하면)
	PostProcess  UMETA(DisplayName="PostProcess"),  // 흑백/왜곡 등
	PoseState    UMETA(DisplayName="PoseState")     // 노인자세 등
};

USTRUCT(BlueprintType)
struct FStatEffectMessage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStatEffectType Type = EStatEffectType::None;

	// 체력/스탯 변화량 (0~1 기준)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delta01 = 0.f;

	// UI에 보여줄 이유(짧게)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Reason;

	// 아이콘(없어도 됨)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon = nullptr;

	// 칩이 화면에 남는 시간(초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DurationSec = 1.2f;

	// “연속 입력 합치기” 같은 정책에 쓰기 좋음
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanStack = true;

	// 디버깅/로그용
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SourceEventId = NAME_None;
};
