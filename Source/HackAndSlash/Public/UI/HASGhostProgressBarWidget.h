// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HASUserWidgetBase.h"
#include "HASGhostProgressBarWidget.generated.h"

class UImage;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASGhostProgressBarWidget : public UHASUserWidgetBase
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;

public: 
	void SetProgressBarValue(float NewValue, bool bForceReset = false);

public:
	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	FName MainValueName = "MainProgress";

	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	FName GhostValueName = "GhostProgress";

	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	float StartSyncGhostBarWaitTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	float SyncGhostBarTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	float SyncGhostBarSpeed = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Ghost Progress Bar")
	TObjectPtr<UMaterialInterface> ProgressBarMI;

protected: 
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> ProgressBarImg;

	UPROPERTY()
		TObjectPtr<UMaterialInstanceDynamic> ProgressBarDynMI;

private: 
	float MainValue;
	float GhostValue;

	float SyncGhostBarTimeCounter;
	FTimerHandle SyncGhostBarTimerHandle;

private: 
	UFUNCTION()
	void HandleSyncGhostBarTimer();
};
