// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <AbilitySystemInterface.h>
#include "HASCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeadSignature, uint32);

class UHASAbilitySystemComponent;
class USpringArmComponent;
class UCameraComponent;
class UGameplayEffect;
class UMotionWarpingComponent;

UCLASS()
class HACKANDSLASH_API AHASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHASCharacterBase(const FObjectInitializer& ObjectInitilizer);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// IAbilitySystemInterface implementation
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

public: 
	FOnDeadSignature OnDead;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	TObjectPtr<UHASAbilitySystemComponent> AbilityComp;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Movement")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComp;

public: 
	UMotionWarpingComponent* GetMotionWarpingComp() const { return MotionWarpingComp; }
	bool IsDead() const;

protected: 
	virtual void Die();
};
