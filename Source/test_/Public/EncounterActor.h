#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EncounterActor.generated.h"

// ✅ 클래스 선언 위에 추가
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnApproachFinished);

UCLASS()
class TEST__API AEncounterActor : public AActor
{
    GENERATED_BODY()

public:
    AEncounterActor();

    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Encounter")
    virtual void StartApproach(const FTransform& StartTransform, const FTransform& TargetTransform);

    UFUNCTION(BlueprintCallable, Category="Encounter")
    virtual void Despawn(float LifeSpanSeconds = 1.5f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter")
    bool bApproaching = true;

    UPROPERTY(BlueprintAssignable)
    FOnApproachFinished OnApproachFinished;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter")
    float ApproachDuration = 2.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Encounter")
    bool bSnapToGround = true;

private:
    float Elapsed = 0.0f;
    FVector StartLoc = FVector::ZeroVector;
    FVector TargetLoc = FVector::ZeroVector;
    FRotator FaceRot = FRotator::ZeroRotator;
};