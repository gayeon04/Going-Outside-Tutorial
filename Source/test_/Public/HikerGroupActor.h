#pragma once

#include "CoreMinimal.h"
#include "EncounterActor.h"              // ✅ 부모 include
#include "HikerGroupActor.generated.h"

UENUM(BlueprintType)
enum class EStepAsideSide : uint8
{
    Left  UMETA(DisplayName="Left"),
    Right UMETA(DisplayName="Right")
};

UCLASS()
class TEST__API AHikerGroupActor : public AEncounterActor
{
    GENERATED_BODY()

public:
    AHikerGroupActor();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

public:
    // ===== Tunables =====
    // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    // float ApproachDuration = 2.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float StopDistance = 120.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float StepAsideDistance = 180.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float FormationSpacing = 90.f;

    // ❌ bSnapToGround는 부모(AEncounterActor)에 이미 있음. 여기선 선언하지 말 것.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float GroundTraceUp = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float GroundTraceDown = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float FormationSpacing_Block = 90.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HikerGroup|Tuning")
    float FormationSpacing_Open = 220.f;

public:
    // ===== Public API =====
    // ❌ 부모가 이미 UFUNCTION 이므로 여기선 UFUNCTION 붙이면 안됨
    virtual void StartApproach(const FTransform& StartTransform, const FTransform& BlockTransform) override;

    UFUNCTION(BlueprintCallable, Category="HikerGroup")
    void StepAside(EStepAsideSide Side);

    // ❌ 부모가 이미 UFUNCTION 이므로 여기선 UFUNCTION 붙이면 안됨
    virtual void Despawn(float LifeSpanSeconds = 1.5f) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="HikerGroup|Runtime")
    bool bFormationOpened = false;

protected:
    // ===== Components =====
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HikerGroup|Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HikerGroup|Components")
    USkeletalMeshComponent* Hiker1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HikerGroup|Components")
    USkeletalMeshComponent* Hiker2;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HikerGroup|Components")
    USkeletalMeshComponent* Hiker3;

private:
    // runtime
    bool bApproaching = false;
    float Elapsed = 0.f;

    FVector StartLoc;
    FVector TargetLoc;
    FRotator FaceRot;

    void UpdateFormationAtLocation(const FVector& GroupWorldLoc);
    FVector SnapLocationToGroundIfNeeded(const FVector& InLoc) const;

    void ResetFormation();
    void ApplyFormationSpacing(float Spacing);
};
