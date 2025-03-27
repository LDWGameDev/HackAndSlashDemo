// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_ActivateAbility.h"
#include <AbilitySystemComponent.h>
#include <AbilitySystemGlobals.h>
#include <AIController.h>

EBTNodeResult::Type UBTTask_ActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner())
	{
		return EBTNodeResult::Type::Failed;
	}

	if (UAbilitySystemComponent* AbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerComp.GetAIOwner()->GetPawn()))
	{
		AbilityComp->TryActivateAbilitiesByTag(AbilityTag);
	}

	return EBTNodeResult::Type::Succeeded;
}
