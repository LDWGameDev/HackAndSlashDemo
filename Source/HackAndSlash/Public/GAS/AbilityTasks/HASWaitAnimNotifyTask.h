// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HASWaitAnimNotifyTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReceivedNotifyEventSignature);

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASWaitAnimNotifyTask : public UAbilityTask
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UHASWaitAnimNotifyTask* WaitAnimNotify(UGameplayAbility* OwningAbility, FString NotifyEvent);

	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnding) override;

public: 
	UPROPERTY(BlueprintAssignable)
	FOnReceivedNotifyEventSignature OnReceivedExactEvent;

	UPROPERTY(BlueprintAssignable)
	FOnReceivedNotifyEventSignature OnReceivedOtherEvent;

private: 
	FString Event;

protected: 
	UFUNCTION()
	void HandleOnReceivedNotifyEvent(const FString& NotifyEvent);
};
