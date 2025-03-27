// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "HASPlayAnimWithNotiEvent.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASPlayAnimWithNotiEvent : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UHASPlayAnimWithNotiEvent* PlayAnimationWithNotifyEvent(UGameplayAbility* OwningAbility);

	virtual void Activate() override;

protected: 
	virtual void OnDestroy(bool bInOwnerFinished) override;
};
