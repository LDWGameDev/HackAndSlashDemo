// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/HASPlayerCharacter.h"
#include "Movement/HASCharacterMovementComponent.h"
#include "GAS/Attribute/HASPlayerAttributeSet.h"
#include "Input/HASEnhancedInputComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "HASGameplayTags.h"
#include "Settings/HASGameUserSettings.h"
#include "GAS/HASAbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <GameplayEffectTypes.h>

AHASPlayerCharacter::AHASPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UHASCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;

	PlayerAttributeSet = CreateDefaultSubobject<UHASPlayerAttributeSet>(TEXT("Player Attribute Set"));

	FollowSpringArmComp = CreateDefaultSubobject<USpringArmComponent>("Follow Spring Arm Component");
	FollowSpringArmComp->SetupAttachment(GetRootComponent());

	FollowCameraComp = CreateDefaultSubobject<UCameraComponent>("Follow Camera Component");
	FollowCameraComp->SetupAttachment(FollowSpringArmComp);

	GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
}

void AHASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(StaminaRecoveryHandle, this, &ThisClass::HandleStaminaRecovery, StaminaRecoveryInterval, true, 0.0f);

	if (AbilityComp && PlayerAttributeSet)
	{
		FOnGameplayAttributeValueChange& HealthChangeDelegate = AbilityComp->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetCurrentHealthAttribute());
		HealthChangeDelegate.AddUObject(this, &ThisClass::HandleOnCurrentHealthChanged);
	}
}

void AHASPlayerCharacter::Die()
{
	Super::Die();
}

void AHASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UHASEnhancedInputComponent* EnhancedInputComp = Cast<UHASEnhancedInputComponent>(PlayerInputComponent);
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	check(EnhancedInputComp);

	EnhancedInputComp->InitInputs(DefaultInputConfig, LocalPlayer);
	EnhancedInputComp->OnProcessedTriggeredInputsDelegate.AddUObject(this, &ThisClass::HandleOnProcessedTriggeredInputs);
	EnhancedInputComp->OnProcessedCancelledInputsDelegate.AddUObject(this, &ThisClass::HandleOnProcessedCancelledInputs);

	EnhancedInputComp->BindNormalInputActionByTag(this, DefaultInputConfig, FHASGameplayTags::Get().InputTag_Movement, ETriggerEvent::Triggered, &ThisClass::HandleMovementInputTriggered);
	EnhancedInputComp->BindNormalInputActionByTag(this, DefaultInputConfig, FHASGameplayTags::Get().InputTag_Movement, ETriggerEvent::Completed, &ThisClass::HandleMovementInputCompleted);
	EnhancedInputComp->BindNormalInputActionByTag(this, DefaultInputConfig, FHASGameplayTags::Get().InputTag_CursorDelta, ETriggerEvent::Triggered, &ThisClass::HandleCursorDeltaInput);
}

FVector2D AHASPlayerCharacter::GetComputedMovementInputSpeed()
{
	if (!PlayerAttributeSet) return FVector2D();
	FGameplayAttributeData* SpeedAttributeData = PlayerAttributeSet->GetSpeedAttribute().GetGameplayAttributeData(PlayerAttributeSet);
	if (!SpeedAttributeData) return FVector2D();
	
	float NormalizedSpeed = SpeedAttributeData->GetCurrentValue() / SpeedAttributeData->GetBaseValue();

	FVector Velocity = GetVelocity();
	Velocity.Z = 0.0f;
	Velocity.Normalize();

	FVector ComputedMovementDirection;
	ComputedMovementDirection.X = FVector::DotProduct(GetActorRightVector(), Velocity);
	ComputedMovementDirection.Y = FVector::DotProduct(GetActorForwardVector(), Velocity);

	return (FVector2D(ComputedMovementDirection.X, ComputedMovementDirection.Y) * NormalizedSpeed);
}

void AHASPlayerCharacter::HandleMovementInputTriggered(const FInputActionValue& InputActionValue)
{
	if (!FollowCameraComp) return;
	FVector2D MovementInput = InputActionValue.Get<FVector2D>();
	LastMovementInput = MovementInput;
	
	FVector FollowCamForward = FollowCameraComp->GetForwardVector();
	FollowCamForward.Z = 0.0f;
	FollowCamForward.Normalize();

	FVector FollowCamRight = FollowCameraComp->GetRightVector();
	FollowCamRight.Z = 0.0f;
	FollowCamRight.Normalize();

	FVector ComputedDirection = FollowCamForward * MovementInput.Y + FollowCamRight * MovementInput.X;
	ComputedDirection.Normalize();

	AddMovementInput(ComputedDirection, 1.0f, false);
}

void AHASPlayerCharacter::HandleMovementInputCompleted(const FInputActionValue& InputActionValue)
{
	LastMovementInput = FVector2D(0.0f, 0.0f);
}

void AHASPlayerCharacter::HandleCursorDeltaInput(const FInputActionValue& InputActionValue)
{
	if (!FollowCameraComp) return;
	FVector2D CursorDeltaInput = InputActionValue.Get<FVector2D>();

	// TODO: multiply with mouse sensitive setting
	AddControllerYawInput(CursorDeltaInput.X * UHASGameUserSettings::Get()->GetMouseSensitivity());
	AddControllerPitchInput(-CursorDeltaInput.Y * UHASGameUserSettings::Get()->GetMouseSensitivity());
}

void AHASPlayerCharacter::HandleOnProcessedTriggeredInputs(TArray<FGameplayTag> TriggeredTags)
{
	if (AbilityComp)
	{
		AbilityComp->ProcessTriggeredInputs(TriggeredTags);
	}

	// TEST: Send gameplay event instead of manually trigger ability
	//for (FGameplayTag& TagIter : TriggeredTags)
	//{
	//	FGameplayEventData Payload;
	//	Payload.EventTag = TagIter;
	//	Payload.Instigator = this;
	//	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, TagIter, Payload);
	//}
}

void AHASPlayerCharacter::HandleOnProcessedCancelledInputs(TArray<FGameplayTag> CancelledTags)
{
	if (AbilityComp)
	{
		AbilityComp->ProcessCancelledInputs(CancelledTags);
	}
}

void AHASPlayerCharacter::HandleStaminaRecovery()
{
	if (StaminaRecoveryGE && AbilityComp)
	{
		AbilityComp->QuickApplyGE(StaminaRecoveryGE);
	}
}

void AHASPlayerCharacter::HandleOnCurrentHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	if (ChangeData.NewValue <= 0 && !bIsDead)
	{
		Die();
		bIsDead = true;
	}
}

