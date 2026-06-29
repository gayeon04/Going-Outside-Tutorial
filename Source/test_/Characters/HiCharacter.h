
#pragma once

#include "CoreMinimal.h"
#include "AlsCharacterExample.h"
#include "HiCharacter.generated.h"

class USkeletalMeshComponent;
class UInputAction;

UCLASS(Blueprintable, BlueprintType)
class TEST__API AHiCharacter : public AAlsCharacterExample
{
	GENERATED_BODY()

public:
	AHiCharacter();

	USkeletalMeshComponent* GetVisibleMeshComponent() const { return VisibleMeshComponent; }

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	virtual void Input_OnAim(const FInputActionValue& ActionValue) override;

	virtual void Input_Interact(const FInputActionValue& ActionValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTryInteract(class AHiPickupBase* TargetPickupBase);

	void AddMappingContext(UInputMappingContext* Context);
	void RemoveMappingContext(UInputMappingContext* Context);


protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> VisibleMeshComponent = nullptr;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHiInteractionComponent> InteractionComponent = nullptr;


	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> MouseLeftAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Als Character Example", Meta = (DisplayThumbnail = false))
	TObjectPtr<UInputAction> InteractAction;


	UPROPERTY(Transient)
	UAnimMontage* CurrentPlayingMontage = nullptr;

	FGameplayTagContainer AnimationTags;
};
