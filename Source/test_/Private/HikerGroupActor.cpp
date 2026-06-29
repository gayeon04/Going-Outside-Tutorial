#include "HikerGroupActor.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AHikerGroupActor::AHikerGroupActor()
{
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    Hiker1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hiker1"));
    Hiker1->SetupAttachment(Root);
    Hiker1->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Hiker2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hiker2"));
    Hiker2->SetupAttachment(Root);
    Hiker2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Hiker3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hiker3"));
    Hiker3->SetupAttachment(Root);
    Hiker3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AHikerGroupActor::BeginPlay()
{
    Super::BeginPlay();
}

void AHikerGroupActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!bApproaching)
        return;

    const float Duration = FMath::Max(0.05f, ApproachDuration);
    Elapsed += DeltaSeconds;

    const float Alpha = FMath::Clamp(Elapsed / Duration, 0.f, 1.f);

    // Linear move of the group actor (world)
    FVector NewLoc = FMath::Lerp(StartLoc, TargetLoc, Alpha);
    NewLoc = SnapLocationToGroundIfNeeded(NewLoc);

    SetActorLocation(NewLoc);
    SetActorRotation(FaceRot);

    if (Alpha >= 1.f)
    {
        bApproaching = false;
    }
}

void AHikerGroupActor::StartApproach(const FTransform& StartTransform, const FTransform& BlockTransform)
{
    StartLoc = StartTransform.GetLocation();

    const FVector BlockLoc = BlockTransform.GetLocation();
    const FVector DirToPlayer = (BlockLoc - StartLoc).GetSafeNormal();
    const FVector StopLoc = BlockLoc - DirToPlayer * StopDistance;

    TargetLoc = StopLoc;

    FaceRot = DirToPlayer.Rotation();

    SetActorLocation(SnapLocationToGroundIfNeeded(StartLoc));
    SetActorRotation(FaceRot);

    // place hikers in a line or simple formation immediately
    UpdateFormationAtLocation(GetActorLocation());

    Elapsed = 0.f;
    bApproaching = true;

    UE_LOG(LogTemp, Warning, TEXT("[HikerGroup] StartApproach %s"), *GetName());
}

void AHikerGroupActor::StepAside(EStepAsideSide Side)
{
    bFormationOpened = true;
    ApplyFormationSpacing(FormationSpacing_Open);
    UE_LOG(LogTemp, Warning, TEXT("[HikerGroup] StepAside -> OpenGap (Open=%.1f)"), FormationSpacing_Open);
}

void AHikerGroupActor::ResetFormation()
{
    bFormationOpened = false;
    ApplyFormationSpacing(FormationSpacing_Block);
}



void AHikerGroupActor::Despawn(float LifeSpanSeconds)
{
    SetLifeSpan(FMath::Max(0.1f, LifeSpanSeconds));
}

void AHikerGroupActor::UpdateFormationAtLocation(const FVector& /*GroupWorldLoc*/)
{
    ApplyFormationSpacing(bFormationOpened ? FormationSpacing_Open : FormationSpacing_Block);
}


FVector AHikerGroupActor::SnapLocationToGroundIfNeeded(const FVector& InLoc) const
{
    if (!bSnapToGround)
        return InLoc;

    UWorld* World = GetWorld();
    if (!World)
        return InLoc;

    const FVector Start = InLoc + FVector(0,0, GroundTraceUp);
    const FVector End   = InLoc - FVector(0,0, GroundTraceDown);

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(HikerGroundSnap), false);

    // WorldStatic 위주로 스냅
    const bool bHit = World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
    if (bHit)
    {
        FVector Out = InLoc;
        Out.Z = Hit.ImpactPoint.Z;
        return Out;
    }

    return InLoc;
}
void AHikerGroupActor::ApplyFormationSpacing(float Spacing)
{
    const FVector Left  = -FVector::RightVector * Spacing;
    const FVector Mid   = FVector::ZeroVector;
    const FVector Right =  FVector::RightVector * Spacing;

    Hiker1->SetRelativeLocation(Left);
    Hiker2->SetRelativeLocation(Mid);
    Hiker3->SetRelativeLocation(Right);
}
