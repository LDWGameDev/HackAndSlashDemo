// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASGhostProgressBarWidget.h"
#include <Kismet/KismetMaterialLibrary.h>
#include <Materials/MaterialInterface.h>
#include <Components/Image.h>

void UHASGhostProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ProgressBarMI && ProgressBarImg)
	{
		ProgressBarDynMI = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, ProgressBarMI);
		ProgressBarImg->SetBrushFromMaterial(ProgressBarDynMI);
	}
	SetProgressBarValue(1.0f, true);
}

void UHASGhostProgressBarWidget::SetProgressBarValue(float NewValue, bool bForceReset /*= false*/)
{
	float ClampedNewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
	float LastMainValue = MainValue;
	MainValue = ClampedNewValue;

	if (!ProgressBarDynMI) return;
	ProgressBarDynMI->SetScalarParameterValue(MainValueName, MainValue);
	
	if (LastMainValue > MainValue)
	{
		GhostValue += LastMainValue - MainValue;
		if (!GetWorld()->GetTimerManager().IsTimerActive(SyncGhostBarTimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(SyncGhostBarTimerHandle, this, &ThisClass::HandleSyncGhostBarTimer, GetWorld()->DeltaTimeSeconds, true, 0.0f);
		}
		else
		{
			SyncGhostBarTimeCounter = 0.0f;
		}
	}
	if (bForceReset)
	{
		GhostValue = 0.0f;
		ProgressBarDynMI->SetScalarParameterValue(GhostValueName, GhostValue);
	}
}

void UHASGhostProgressBarWidget::HandleSyncGhostBarTimer()
{
	float WorldDeltaTime = GetWorld()->DeltaTimeSeconds;
	SyncGhostBarTimeCounter += WorldDeltaTime;

	GhostValue = FMath::FInterpTo(GhostValue, 0.0f, WorldDeltaTime, SyncGhostBarSpeed);

	if (ProgressBarDynMI)
	{
		ProgressBarDynMI->SetScalarParameterValue(GhostValueName, GhostValue);
	}
	
	if (SyncGhostBarTimeCounter >= SyncGhostBarTime)
	{
		SyncGhostBarTimeCounter = 0.0f;
		GetWorld()->GetTimerManager().ClearTimer(SyncGhostBarTimerHandle);
		
		GhostValue = 0.0f;
		if (ProgressBarDynMI)
		{
			ProgressBarDynMI->SetScalarParameterValue(GhostValueName, GhostValue);
		}
	}
}
