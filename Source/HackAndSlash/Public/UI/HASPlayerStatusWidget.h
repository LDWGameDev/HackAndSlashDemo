// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HASUserWidgetBase.h"
#include <GameplayEffectTypes.h>
#include "HASPlayerStatusWidget.generated.h"

class UHASGhostProgressBarWidget;
class UHASPlayerAttributeSet;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASPlayerStatusWidget : public UHASUserWidgetBase
{
	GENERATED_BODY()
	
public: 
	virtual void NativePreConstruct() override;

protected: 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHASGhostProgressBarWidget> HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHASGhostProgressBarWidget> StaminaBar;

public: 
	void BindToAttributeChanges();

private:
	UHASPlayerAttributeSet* GetPlayerAttributeSet();

	void HandleOnChangedCurrentHealthAttribute(const FOnAttributeChangeData& ChangeData);
	void HandleOnChangedMaxHealthAttribute(const FOnAttributeChangeData& ChangeData);

	void HandleOnChangedCurrentStaminaAttribute(const FOnAttributeChangeData& ChangeData);
	void HandleOnChangedMaxStaminaAttribute(const FOnAttributeChangeData& ChangeData);
};
