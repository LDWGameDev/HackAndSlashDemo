// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/HASAnimInstanceBase.h"
#include "HASPlayerAnimInstance.generated.h"

class AHASPlayerCharacter;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASPlayerAnimInstance : public UHASAnimInstanceBase
{
	GENERATED_BODY()
	
public: 
	UHASPlayerAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	float ForwardDirectionValue;
	UPROPERTY(BlueprintReadOnly)
	float RightDirectionValue;
	UPROPERTY(BlueprintReadOnly)
	bool bFalling = false;

	UPROPERTY()
	TObjectPtr<AHASPlayerCharacter> OwnerChar;
};
