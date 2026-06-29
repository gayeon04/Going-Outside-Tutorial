// Fill out your copyright notice in the Description page of Project Settings.

#include "HiAISpawner.h"
#include "HiAICharacter.h"
#include "HiAIController.h"
#include "Components/BoxComponent.h"
#include "Data/HiAICharacterData.h"
#include "Kismet/KismetMathLibrary.h"


AHiAISpawner::AHiAISpawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxComp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BrushComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
}

void AHiAISpawner::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World || !AICharacterData)
		return;

	for (const FGameplayTag& CharTag : StartupCharacterTags)
	{
		if (!CharTag.IsValid())
			continue;

		UHiCharacterStartData* StartData = AICharacterData->GetStartDataByTag(CharTag);
		if (!StartData || !StartData->IsValid())
			continue;

		AHiAICharacter* NewAIChar = World->SpawnActorDeferred<AHiAICharacter>(AICharClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		if (!NewAIChar)
			continue;

		const FVector SpawnLocation = GetRandomPointInRange();
		FTransform SpawnTransform = FTransform::Identity;
		SpawnTransform.SetLocation(SpawnLocation);

		NewAIChar->SetDesiredGait(StartData->GaitTag);

		USkeletalMesh* VisibleMesh = StartData->VisibleMesh;
		USkeletalMeshComponent* VisibleMeshComp = NewAIChar->GetVisibleMeshComponent();
		check(VisibleMeshComp);
		VisibleMeshComp->SetSkeletalMesh(VisibleMesh);

		NewAIChar->FinishSpawning(SpawnTransform);

		UBehaviorTree* BT = StartData->BT;
		check(BT);
		AAIController* AIController = NewAIChar->GetAIController();
		check(AIController);
		AIController->RunBehaviorTree(BT);
	}
}

void AHiAISpawner::BeginDestroy()
{
	Super::BeginDestroy();
}

FVector AHiAISpawner::GetRandomPointInRange() const
{
	const FBoxSphereBounds BrushBounds = BoxComp->CalcBounds(BoxComp->GetComponentTransform());
	return UKismetMathLibrary::RandomPointInBoundingBox(BrushBounds.Origin, BrushBounds.BoxExtent);
}
