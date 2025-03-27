// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HASPlayerController.h"
#include <AbilitySystemComponent.h>
#include <AbilitySystemInterface.h>
#include "Input/HASEnhancedInputComponent.h"
#include "UI/HASHUDWidget.h"
#include "HASPlayerStatusSubsystem.h"
#include "GameModes/HASZoneGS.h"
#include "Characters/Player/HASPlayerCharacter.h"

void AHASPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PostProcessInput(DeltaTime, bGamePaused);

	if (!GetPawn() || !GetPawn()->InputComponent) return;
	if (UHASEnhancedInputComponent* EnhancedInputComp = Cast<UHASEnhancedInputComponent>(GetPawn()->InputComponent))
	{
		EnhancedInputComp->ProcessCachedInputs();
	}
}

UAbilitySystemComponent* AHASPlayerController::GetAbilitySystemComponent() const
{
	if (IAbilitySystemInterface* PawnAbilityInterface = Cast<IAbilitySystemInterface>(GetPawn()))
	{
		return PawnAbilityInterface->GetAbilitySystemComponent();
	}
	return nullptr;
}

void AHASPlayerController::BeginPlay()
{
	if (AHASZoneGS* ZoneGS = GetWorld()->GetGameState<AHASZoneGS>())
	{
		ZoneGS->OnWon.AddUObject(this, &ThisClass::HandleOnMatchWon);
	}

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	SetShowMouseCursor(false);
}

void AHASPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (HUDClass)
	{
		HUDWidget = CreateWidget<UHASHUDWidget>(this, HUDClass);
		HUDWidget->AddToViewport(0);
		HUDWidget->BindRelevantDependencies();
	}
	UHASPlayerStatusSubsystem::Get(this)->OnComboCountUpdated.AddUObject(this, &ThisClass::HandleOnComboCountUpdated);
	
	if (AHASPlayerCharacter* PlayerChar = Cast<AHASPlayerCharacter>(aPawn))
	{
		PlayerChar->OnDead.AddUObject(this, &ThisClass::HandlePossessedPawnDead);
	}
}

void AHASPlayerController::HandleOnComboCountUpdated(int32 ComboCount)
{
	if (HUDWidget)
	{
		HUDWidget->UpdateComboCount(ComboCount);
	}
}

void AHASPlayerController::HandleOnMatchWon()
{
	if (HUDWidget)
	{
		HUDWidget->ShowWinningScreen();
	}
}

void AHASPlayerController::HandlePossessedPawnDead(uint32 PawnId)
{
	if (HUDWidget)
	{
		HUDWidget->ShowLosingScreen();
	}
}

