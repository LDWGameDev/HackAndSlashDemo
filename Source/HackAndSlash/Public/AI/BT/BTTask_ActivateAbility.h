// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include <GameplayTagContainer.h>
#include "BTTask_ActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UBTTask_ActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()
	
protected: 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public: 
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer AbilityTag;
};
