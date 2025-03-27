// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/HASAnimNotify_ApplyGE.h"
#include <AbilitySystemComponent.h>
#include <GameplayEffectTypes.h>
#include <AbilitySystemGlobals.h>

UHASAnimNotify_ApplyGE::UHASAnimNotify_ApplyGE()
{

}

void UHASAnimNotify_ApplyGE::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !GE) return;
	AActor* OwnerActor = MeshComp->GetOwner();
	if (UAbilitySystemComponent* AbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor))
	{
		FGameplayEffectContextHandle ContextHandle = AbilityComp->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilityComp->MakeOutgoingSpec(GE, 1.0f, ContextHandle);
		GEHandle = AbilityComp->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UHASAnimNotify_ApplyGE::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !GE) return;
	AActor* OwnerActor = MeshComp->GetOwner();
	if (UAbilitySystemComponent* AbilityComp = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(OwnerActor))
	{
		AbilityComp->RemoveActiveGameplayEffect(GEHandle, -1);
	}
}
