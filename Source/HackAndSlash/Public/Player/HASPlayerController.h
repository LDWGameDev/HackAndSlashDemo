// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/HASPlayerControllerBase.h"
#include <AbilitySystemInterface.h>
#include "HASPlayerController.generated.h"

class UAbilitySystemComponent;
class UHASHUDWidget;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API AHASPlayerController : public AHASPlayerControllerBase, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public: 
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

protected: 
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHASHUDWidget> HUDClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UHASHUDWidget> HUDWidget;

	void HandleOnComboCountUpdated(int32 ComboCount);
	void HandleOnMatchWon();
	void HandlePossessedPawnDead(uint32 PawnId);
};
