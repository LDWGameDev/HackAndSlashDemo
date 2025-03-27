// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include <GameplayTagContainer.h>
#include "HASAnimNotify_BroadcastEvent.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Broadcast Event"))
class HACKANDSLASH_API UHASAnimNotify_BroadcastEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UHASAnimNotify_BroadcastEvent();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	virtual FString GetNotifyName_Implementation() const override;

protected: 
	UPROPERTY(EditAnywhere)
	FString NotifyEvent;

	UPROPERTY(EditAnywhere)
	FString NotifyName = TEXT("Broadcast event");
};
