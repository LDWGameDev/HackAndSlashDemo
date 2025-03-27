// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HASUserWidgetBase.h"
#include "HASHUDWidget.generated.h"

class UHASPlayerStatusWidget;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASHUDWidget : public UHASUserWidgetBase
{
	GENERATED_BODY()
	
protected: 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHASPlayerStatusWidget> PlayerStatusWidget;

public:
	void BindRelevantDependencies();

	UFUNCTION(BlueprintNativeEvent)
	void UpdateComboCount(int32 ComboCount);

	UFUNCTION(BlueprintNativeEvent)
	void ShowWinningScreen();

	UFUNCTION(BlueprintNativeEvent)
	void ShowLosingScreen();
};
