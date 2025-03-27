// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HASHUDWidget.h"
#include "UI/HASPlayerStatusWidget.h"

void UHASHUDWidget::BindRelevantDependencies()
{
	if (PlayerStatusWidget)
	{
		PlayerStatusWidget->BindToAttributeChanges();
	}
}

void UHASHUDWidget::UpdateComboCount_Implementation(int32 ComboCount)
{

}

void UHASHUDWidget::ShowWinningScreen_Implementation()
{

}

void UHASHUDWidget::ShowLosingScreen_Implementation()
{

}
