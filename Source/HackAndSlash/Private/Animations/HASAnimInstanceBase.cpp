// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/HASAnimInstanceBase.h"

void UHASAnimInstanceBase::BroadcastNotifyEvent(const FString& NotifyEvent)
{
	OnReceivedNotifyEvent.Broadcast(NotifyEvent);
}
