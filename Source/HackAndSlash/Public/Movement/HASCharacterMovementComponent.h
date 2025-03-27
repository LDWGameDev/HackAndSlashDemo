// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <ActiveGameplayEffectHandle.h>
#include "HASCharacterMovementComponent.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public: 
	virtual void BeginPlay() override;
	virtual float GetMaxSpeed() const override;

protected: 
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode);

protected: 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> FallingActionGE;

	FActiveGameplayEffectHandle EffectHandle;
};
