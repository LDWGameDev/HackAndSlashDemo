// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayTagContainer.h>
#include "HASInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT()
struct FHASInputAction
{
	GENERATED_BODY()

public: 
	FHASInputAction() {}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameplayTag;
};

USTRUCT()
struct FHASInputMappingContext
{
	GENERATED_BODY()

public:
	FHASInputMappingContext() {}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly)
	int32 Priority;
};

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditDefaultsOnly)
	TArray<FHASInputAction> NormalInputActions;

	UPROPERTY(EditDefaultsOnly)
	TArray<FHASInputAction> AbilityInputActions;

	// First mapping context (at index 0) is the default auto-activated one
	UPROPERTY(EditDefaultsOnly)
	TArray<FHASInputMappingContext> InputMappingContexts;

public: 
	UInputAction* FindNormalInputAction(const FGameplayTag& Tag);
	UInputAction* FindAbilityInputAction(const FGameplayTag& Tag);
};
