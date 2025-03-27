// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include <GameplayTagContainer.h>
#include "HASAnimInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHASOnReceivedNotifyEventSignature, const FString&, NotifyEvent);

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(BlueprintAssignable)
	FHASOnReceivedNotifyEventSignature OnReceivedNotifyEvent;

public:
	void BroadcastNotifyEvent(const FString& NotifyEvent);
};
