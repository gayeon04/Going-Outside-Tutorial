// Fill out your copyright notice in the Description page of Project Settings.
#include "Interaction/HiPickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"


AHiPickupBase::AHiPickupBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	WidgetComp->SetupAttachment(RootComponent);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHiPickupBase::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AHiPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

