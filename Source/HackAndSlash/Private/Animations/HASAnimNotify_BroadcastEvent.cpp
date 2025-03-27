// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/HASAnimNotify_BroadcastEvent.h"
#include "Animations/HASAnimInstanceBase.h"

UHASAnimNotify_BroadcastEvent::UHASAnimNotify_BroadcastEvent()
{

}

void UHASAnimNotify_BroadcastEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Received_Notify(MeshComp, Animation, EventReference);
	if (!MeshComp) return;
	if (UHASAnimInstanceBase* AnimInstance = Cast<UHASAnimInstanceBase>(MeshComp->GetAnimInstance()))
	{
		AnimInstance->BroadcastNotifyEvent(NotifyEvent);
	}
}

FString UHASAnimNotify_BroadcastEvent::GetNotifyName_Implementation() const
{
	return NotifyName;
}
