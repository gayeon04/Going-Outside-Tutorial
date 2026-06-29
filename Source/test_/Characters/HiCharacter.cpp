#include "Characters/HiCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "test_.h"
#include "Interaction/HiInteractionComponent.h"
#include "Interaction/HiPickupBase.h"

AHiCharacter::AHiCharacter()
{
	VisibleMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VisibleMeshComponent"));
	VisibleMeshComponent->SetupAttachment(GetMesh());
	InteractionComponent = CreateDefaultSubobject<UHiInteractionComponent>(TEXT("InteractionComponent"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AHiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto* EnhancedInput{Cast<UEnhancedInputComponent>(PlayerInputComponent)};
	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Interact);
	}
}

void AHiCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHiCharacter::Input_OnAim(const FInputActionValue& ActionValue)
{
	Super::Input_OnAim(ActionValue);
}

void AHiCharacter::Input_Interact(const FInputActionValue& ActionValue)
{
	const bool bValue = ActionValue.Get<bool>();
	if (bValue)
	{
		if (AHiPickupBase* PickupBase = InteractionComponent->GetFocusedInteractableObject())
		{
			OnTryInteract(PickupBase);
		}
	}
}

void AHiCharacter::AddMappingContext(UInputMappingContext* Context)
{
	const auto* PreviousPlayer{Cast<APlayerController>(PreviousController)};
	if (IsValid(PreviousPlayer))
	{
		auto* InputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PreviousPlayer->GetLocalPlayer())};
		if (IsValid(InputSubsystem))
		{
			FModifyContextOptions Options;
			Options.bNotifyUserSettings = true;
			InputSubsystem->AddMappingContext(Context, 0, Options);
		}
	}
}

void AHiCharacter::RemoveMappingContext(UInputMappingContext* Context)
{
	auto* NewPlayer{Cast<APlayerController>(GetController())};
	if (IsValid(NewPlayer))
	{
		NewPlayer->InputYawScale_DEPRECATED = 1.0f;
		NewPlayer->InputPitchScale_DEPRECATED = 1.0f;
		NewPlayer->InputRollScale_DEPRECATED = 1.0f;

		auto* InputSubsystem{ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(NewPlayer->GetLocalPlayer())};
		if (IsValid(InputSubsystem))
		{
			InputSubsystem->RemoveMappingContext(Context);
		}
	}
}
