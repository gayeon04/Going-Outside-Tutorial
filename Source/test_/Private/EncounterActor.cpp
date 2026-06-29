#include "EncounterActor.h"

AEncounterActor::AEncounterActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEncounterActor::BeginPlay()
{
    Super::BeginPlay();
}

void AEncounterActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!bApproaching)
        return;

    const float Duration = FMath::Max(0.05f, ApproachDuration);
    Elapsed += DeltaSeconds;

    const float Alpha = FMath::Clamp(Elapsed / Duration, 0.f, 1.f);
    const FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);

    SetActorLocation(NewLoc);
    SetActorRotation(FaceRot);

    if (Alpha >= 1.f)
    {
        bApproaching = false;
        OnApproachFinished.Broadcast();
    }
}

void AEncounterActor::StartApproach(const FTransform& StartTransform, const FTransform& TargetTransform)
{
    bApproaching = true;
    StartLoc  = StartTransform.GetLocation();
    TargetLoc = TargetTransform.GetLocation();

    const FVector Dir = (TargetLoc - StartLoc).GetSafeNormal();
    FaceRot = Dir.Rotation();

    SetActorLocation(StartLoc);
    SetActorRotation(FaceRot);

    Elapsed = 0.f;

}
void AEncounterActor::Despawn(float LifeSpanSeconds)
{
    SetLifeSpan(FMath::Max(0.1f, LifeSpanSeconds));
}
