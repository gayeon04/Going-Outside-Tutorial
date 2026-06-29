// PlayerStatComponent.cpp
#include "PlayerStatComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UPlayerStatComponent::UPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().SetTimer(TickTimer, this, &UPlayerStatComponent::StatTick, 0.1f, true);
	}

	// 초기 상태 브로드캐스트
	RefreshLowHealthState();
	MaybeBroadcast();

	InitRandomGold();
}

void UPlayerStatComponent::SetGold(int32 NewGold)
{
    const int32 OldGold = Gold;

    Gold = FMath::Max(0, NewGold); // 음수 방지

    OnGoldChanged.Broadcast(OldGold, Gold);
}

void UPlayerStatComponent::TickComponent(float dt, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(dt, TickType, ThisTickFunction);

	if (bPaused) return;
}

void UPlayerStatComponent::SaveCurrentState()
{
    SavedHealth01 = Health01;
    UE_LOG(LogTemp, Log, TEXT("[Stat] Saved Health: %.2f"), SavedHealth01);
}

void UPlayerStatComponent::RestoreSavedState()
{
    Health01 = SavedHealth01;
    RefreshLowHealthState();
    MaybeBroadcast();
    UE_LOG(LogTemp, Log, TEXT("[Stat] Restored Health: %.2f"), Health01);
}

void UPlayerStatComponent::SetSimPaused(bool bInPaused)
{
    if (bInPaused && !bPaused)
    {
        // 일시정지 시작 시 자동 저장
        SaveCurrentState();
    }
    
    bPaused = bInPaused;
    SetComponentTickEnabled(!bPaused);
}

void UPlayerStatComponent::StatTick()
{
	const float Dt = 0.1f;
	if (bPaused) return;

	// ✅ 단일 체력: 시간 경과 감소/회복
	if (HealthDecayPerSec > 0.f)
	{
		Health01 = Clamp01(Health01 - HealthDecayPerSec * Dt);
	}
	if (HealthRegenPerSec > 0.f)
	{
		Health01 = Clamp01(Health01 + HealthRegenPerSec * Dt);
	}

	RefreshLowHealthState();
	MaybeBroadcast();
}

void UPlayerStatComponent::RefreshLowHealthState()
{
	const bool bWasLow = bLow;

	if (!bLow && Health01 <= LowHealthOn) bLow = true;
	else if (bLow && Health01 >= LowHealthOff) bLow = false;

	if (bWasLow != bLow)
	{
		OnLowHealthChanged.Broadcast(bLow);
	}
}

void UPlayerStatComponent::MaybeBroadcast()
{
	// ✅ 기존 UI 호환 유지: Thirst/Hunger는 0으로 고정, Health만 의미 있음
    if (FMath::IsNearlyEqual(Health01, LastBroadcastHealth01, 0.0001f)) return;
    LastBroadcastHealth01 = Health01;

    OnNeedsChanged.Broadcast(0.f, 0.f, Health01);

    if (Health01 <= 0.f) OnPlayerDead.Broadcast();

}

// === 기존 API(호환용) ===
void UPlayerStatComponent::AddThirst01(float Delta01)
{
	Thirst01 = Clamp01(Thirst01 + Delta01);
	MaybeBroadcast();
}
void UPlayerStatComponent::AddHunger01(float Delta01)
{
	Hunger01 = Clamp01(Hunger01 + Delta01);
	MaybeBroadcast();
}
void UPlayerStatComponent::FillThirst(float Percent0to100)
{
	AddThirst01(-FMath::Clamp(Percent0to100/100.f, 0.f, 1.f));
}
void UPlayerStatComponent::FillHunger(float Percent0to100)
{
	AddHunger01(-FMath::Clamp(Percent0to100/100.f, 0.f, 1.f));
}
void UPlayerStatComponent::ApplyDamage01(float Amount01)
{
	Health01 = Clamp01(Health01 - FMath::Max(0.f, Amount01));

	if (Health01 <= 0.f)
    {
        OnPlayerDead.Broadcast(); // 델리게이트
    }

	RefreshLowHealthState();
	MaybeBroadcast();
}
void UPlayerStatComponent::Heal01(float Amount01)
{
	Health01 = Clamp01(Health01 + FMath::Max(0.f, Amount01));
	RefreshLowHealthState();
	MaybeBroadcast();
}
void UPlayerStatComponent::Water01(float Amount01)
{
	Thirst01 *= -1;
	Thirst01 = Clamp01(Thirst01 + FMath::Max(0.f, Amount01));
	MaybeBroadcast();
}

// ✅ 새 API: 이유 포함 체력 증감
void UPlayerStatComponent::AddHealth01(float Delta01, FText Reason)
{
	const float Old = Health01;
	Health01 = Clamp01(Health01 + Delta01);

	RefreshLowHealthState();
	MaybeBroadcast();

	if (!Reason.IsEmpty())
	{
		const float Applied = Health01 - Old; // 클램프 반영 후 실제 변화량
		OnHealthReason.Broadcast(Reason, Applied);
	}
}

void UPlayerStatComponent::AddHealth01WithEffect(float Delta01, const FText& Reason, EStatEffectType Type,
                                                UTexture2D* Icon, float DurationSec, FName SourceEventId)
{
	const float Old = Health01;
	Health01 = Clamp01(Health01 + Delta01);

	RefreshLowHealthState();
	MaybeBroadcast();

	// 실제로 적용된 델타(클램프 반영)
	const float Applied = Health01 - Old;

	FStatEffectMessage Msg;
	Msg.Type = (Type == EStatEffectType::None) ? EStatEffectType::HealthDelta : Type;
	Msg.Delta01 = Applied;
	Msg.Reason = Reason;
	Msg.Icon = Icon;
	Msg.DurationSec = FMath::Max(0.1f, DurationSec);
	Msg.bCanStack = true;
	Msg.SourceEventId = SourceEventId;

	OnStatEffectMessage.Broadcast(Msg);
}
// 기존 PlayerStatComponent.cpp 맨 아래에 아래 두 함수를 추가하세요.

void UPlayerStatComponent::InitRandomGold(int32 MinGold, int32 MaxGold)
{
    const int32 Old = Gold;
    Gold = FMath::RandRange(MinGold, MaxGold);
    OnGoldChanged.Broadcast(Old, Gold);
}

int32 UPlayerStatComponent::AddGoldWithEffect(int32 DeltaGold, const FText& Reason,
                                               UTexture2D* Icon, float DurationSec,
                                               FName SourceEventId)
{
    const int32 Old = Gold;

    // 소비 시 잔액 이하로 내려가지 않도록 클램프
    const int32 Applied = (DeltaGold < 0)
        ? FMath::Max(DeltaGold, -Gold)
        : DeltaGold;

    Gold += Applied;
    OnGoldChanged.Broadcast(Old, Gold);

    FStatEffectMessage Msg;
    Msg.Type        = EStatEffectType::None;
    Msg.Delta01     = 0.f;
    Msg.Reason      = Reason;
    Msg.Icon        = Icon;
    Msg.DurationSec = FMath::Max(0.1f, DurationSec);
    Msg.bCanStack   = true;
    Msg.SourceEventId = SourceEventId;
    OnStatEffectMessage.Broadcast(Msg);

    return Applied;
}


void UPlayerStatComponent::ApplyDamagePoints(float DamagePoints, FText Reason)
{
    const float ClampedDamage = FMath::Max(0.f, DamagePoints);
    const float Delta01 = -ClampedDamage / MaxHealthPoints;

    UE_LOG(LogTemp, Warning,
        TEXT("[ApplyDamagePoints] Damage=%.2f Clamped=%.2f MaxHP=%.2f Delta01=%.4f HealthBefore=%.4f"),
        DamagePoints, ClampedDamage, MaxHealthPoints, Delta01, Health01);

    AddHealth01(Delta01, Reason);
}
void UPlayerStatComponent::HealPoints(float HealPoints, FText Reason)
{
    const float Delta01 = FMath::Max(0.f, HealPoints) / MaxHealthPoints;
    AddHealth01(Delta01, Reason);
}

void UPlayerStatComponent::ApplyDamagePointsWithEffect(float DamagePoints, const FText& Reason,
    EStatEffectType Type, UTexture2D* Icon, float DurationSec, FName SourceEventId)
{
    const float Delta01 = -FMath::Max(0.f, DamagePoints) / MaxHealthPoints;
	UE_LOG(LogTemp, Warning, TEXT("[Damage] Points=%.1f, Delta01=%.4f, Health01Before=%.4f"), 
		DamagePoints, Delta01, Health01);
    AddHealth01WithEffect(Delta01, Reason, Type, Icon, DurationSec, SourceEventId);
}

void UPlayerStatComponent::HealPointsWithEffect(float HealPoints, const FText& Reason,
    EStatEffectType Type, UTexture2D* Icon, float DurationSec, FName SourceEventId)  // ← 세미콜론 제거
{
    const float Delta01 = FMath::Max(0.f, HealPoints) / MaxHealthPoints;
    AddHealth01WithEffect(Delta01, Reason, Type, Icon, DurationSec, SourceEventId);
}