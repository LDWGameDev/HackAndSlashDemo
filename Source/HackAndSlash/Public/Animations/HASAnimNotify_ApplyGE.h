// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <ActiveGameplayEffectHandle.h>
#include "HASAnimNotify_ApplyGE.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS(hideCategories = Object, collapseCategories, meta = (DisplayName = "Apply GE"))
class HACKANDSLASH_API UHASAnimNotify_ApplyGE : public UAnimNotifyState
{
	GENERATED_BODY()

public: 
	UHASAnimNotify_ApplyGE();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE;	

	FActiveGameplayEffectHandle GEHandle;
};
