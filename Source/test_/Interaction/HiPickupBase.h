// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HiPickupBase.generated.h"

class AHiCharacter;
class UStaticMeshComponent;
class UWidgetComponent;
class USphereComponent;

UCLASS(BlueprintType)
class TEST__API AHiPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AHiPickupBase();

	virtual void Tick(float DeltaTime) override;

	bool CanInteract() const {return bCanInteract;}
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWidgetComponent> WidgetComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> SphereComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract = false;
};
