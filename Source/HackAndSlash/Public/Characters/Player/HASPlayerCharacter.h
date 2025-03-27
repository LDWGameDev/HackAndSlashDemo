// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/HASCharacterBase.h"
#include <InputActionValue.h>
#include <GameplayTagContainer.h>
#include <GameplayEffectTypes.h>
#include "HASPlayerCharacter.generated.h"

class UHASPlayerAttributeSet;
class UHASInputConfig;
class UGameplayEffect;

UCLASS()
class HACKANDSLASH_API AHASPlayerCharacter : public AHASCharacterBase
{
	GENERATED_BODY()

public:
	AHASPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	virtual void Die() override;

public:
	UPROPERTY(BlueprintReadOnly, Category = "GAS Attribute")
	TObjectPtr<UHASPlayerAttributeSet> PlayerAttributeSet;

protected: 
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCameraComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> FollowSpringArmComp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UHASInputConfig> DefaultInputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute")
	TSubclassOf<UGameplayEffect> StaminaRecoveryGE;

	UPROPERTY(EditDefaultsOnly, Category = "GAS Attribute")
	float StaminaRecoveryInterval = 0.5f;

	FVector2D LastMovementInput;

	FTimerHandle StaminaRecoveryHandle;

	bool bIsDead = false;

public:
	FVector2D GetComputedMovementInputSpeed();

protected: 
	virtual void HandleMovementInputTriggered(const FInputActionValue& InputActionValue);
	virtual void HandleMovementInputCompleted(const FInputActionValue& InputActionValue);
	virtual void HandleCursorDeltaInput(const FInputActionValue& InputActionValue);

	UFUNCTION()
	virtual void HandleOnProcessedTriggeredInputs(TArray<FGameplayTag> TriggeredTags);

	UFUNCTION()
	virtual void HandleOnProcessedCancelledInputs(TArray<FGameplayTag> CancelledTags);

	UFUNCTION()
	void HandleStaminaRecovery();

	void HandleOnCurrentHealthChanged(const FOnAttributeChangeData& ChangeData);
};
