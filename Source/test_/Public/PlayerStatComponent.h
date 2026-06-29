// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatEffectMessage.h"
#include "PlayerStatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNeedsChanged, float, Thirst01, float, Hunger01, float, Health01);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLowHealthChanged, bool, bLow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatEffectMessage, const FStatEffectMessage&, Msg);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthReason, FText, Reason, float, Delta01);

// ── 골드 변화 델리게이트 ──────────────────────────────────────────────────
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGoldChanged, int32, OldGold, int32, NewGold);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDead);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEST__API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerStatComponent();

	// === 체력 ===
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats") float Thirst01 = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats") float Hunger01 = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stats") float Health01 = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rates", meta=(ClampMin="0")) float ThirstRatePerSec = 0.005f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rates", meta=(ClampMin="0")) float HungerRatePerSec = 0.003f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthSingle", meta=(ClampMin="0"))
	float HealthDecayPerSec = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HealthSingle", meta=(ClampMin="0"))
	float HealthRegenPerSec = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Low", meta=(ClampMin="0", ClampMax="1")) float LowHealthOn  = 0.20f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Low", meta=(ClampMin="0", ClampMax="1")) float LowHealthOff = 0.26f;

	// === 골드 ===
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gold")
	int32 Gold = 0;

	/** 랜덤 골드 초기화 (상점 진입 시 호출) */
	UFUNCTION(BlueprintCallable, Category="Gold")
	void InitRandomGold(int32 MinGold = 0, int32 MaxGold = 10000);

	UFUNCTION(BlueprintPure,     Category="Gold")
	int32 GetGold() const { return Gold; }

	UFUNCTION(BlueprintPure,     Category="Gold")
	bool CanAfford(int32 Cost) const { return Gold >= Cost; }

	UFUNCTION(BlueprintCallable, Category="Gold")
	void SetGold(int32 NewGold);

	/**
	 * 골드 증감 + 이펙트 메시지 브로드캐스트.
	 * AddHealth01WithEffect 와 동일한 패턴.
	 */
	UFUNCTION(BlueprintCallable, Category="Gold")
	int32 AddGoldWithEffect(int32 DeltaGold, const FText& Reason,
	                        UTexture2D* Icon, float DurationSec, FName SourceEventId);

	// === 이벤트 ===
	UPROPERTY(BlueprintAssignable, Category="Events") FOnNeedsChanged      OnNeedsChanged;
	UPROPERTY(BlueprintAssignable, Category="Events") FOnLowHealthChanged  OnLowHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="Events") FOnHealthReason      OnHealthReason;
	UPROPERTY(BlueprintAssignable, Category="Events") FOnStatEffectMessage OnStatEffectMessage;
	UPROPERTY(BlueprintAssignable, Category="Gold")   FOnGoldChanged       OnGoldChanged;

	// === 체력 API (기존 그대로) ===
	UFUNCTION(BlueprintCallable, Category="Stats") void AddThirst01(float Delta01);
	UFUNCTION(BlueprintCallable, Category="Stats") void AddHunger01(float Delta01);
	UFUNCTION(BlueprintCallable, Category="Stats") void FillThirst(float Percent0to100);
	UFUNCTION(BlueprintCallable, Category="Stats") void FillHunger(float Percent0to100);
	UFUNCTION(BlueprintCallable, Category="Stats") void ApplyDamage01(float Amount01);
	UFUNCTION(BlueprintCallable, Category="Stats") void Heal01(float Amount01);
	UFUNCTION(BlueprintCallable, Category="Stats") void Water01(float Amount01);

	UFUNCTION(BlueprintCallable, Category="Stats")
	void AddHealth01(float Delta01, FText Reason);

	UFUNCTION(BlueprintCallable, Category="Stats")
	void SetSimPaused(bool bInPaused);

	UFUNCTION(BlueprintPure, Category="Stats")
	bool IsSimPaused() const { return bPaused; }

	UFUNCTION(BlueprintCallable, Category="Stats")
	void AddHealth01WithEffect(float Delta01, const FText& Reason, EStatEffectType Type,
	                           UTexture2D* Icon, float DurationSec, FName SourceEventId);

							   // === 수치 체력 API (1000 기반) ===
	static constexpr float MaxHealthPoints = 1000.f;

	/** 현재 HP를 0~1000 수치로 반환 */
	UFUNCTION(BlueprintPure, Category="Stats")
	float GetHealthPoints() const { return Health01 * MaxHealthPoints; }

	/** 수치로 데미지 적용 (ex. 300 입력 → Health01 -0.3) */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void ApplyDamagePoints(float DamagePoints, FText Reason);

	/** 수치로 회복 적용 */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void HealPoints(float HealPoints, FText Reason);

	/** 수치 데미지 + 이펙트 메시지 (Blueprint용) */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void ApplyDamagePointsWithEffect(float DamagePoints, const FText& Reason, EStatEffectType Type,
									UTexture2D* Icon, float DurationSec, FName SourceEventId);

	/** 수치 회복 + 이펙트 메시지 (Blueprint용) */
	UFUNCTION(BlueprintCallable, Category="Stats")
	void HealPointsWithEffect(float HealPoints, const FText& Reason, EStatEffectType Type,
							UTexture2D* Icon, float DurationSec, FName SourceEventId);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FTimerHandle TickTimer;
	bool bLow = false;

	void StatTick();
	void MaybeBroadcast();
	void RefreshLowHealthState();

	static float Clamp01(float v){ return FMath::Clamp(v, 0.f, 1.f); }

	UPROPERTY(VisibleAnywhere, Category="Stats")
	bool bPaused = false;

	float SavedHealth01 = 1.0f;
	float LastBroadcastHealth01 = -1.f;

public:
	UFUNCTION(BlueprintCallable, Category="Stat") void SaveCurrentState();
	UFUNCTION(BlueprintCallable, Category="Stat") void RestoreSavedState();

	
	UPROPERTY(BlueprintAssignable)
	FOnPlayerDead OnPlayerDead;
};