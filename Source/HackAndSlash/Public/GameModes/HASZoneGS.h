// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/HASGameStateBase.h"
#include "HASZoneGS.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnMatchEndedDelegate);

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API AHASZoneGS : public AHASGameStateBase
{
	GENERATED_BODY()
	
public: 
	AHASZoneGS();

	virtual bool HasMatchStarted() const override;
	virtual bool HasMatchEnded() const override;

protected: 
	virtual void BeginPlay() override;

public: 
	FOnMatchEndedDelegate OnWon;
	FOnMatchEndedDelegate OnLost;

protected: 
	TArray<uint32> ZoneIds;
	bool bAllZoneCleared = false;

protected: 
	void HandleOnZoneCleared(uint32 ZoneId);
	void Win();
	void Lose();
};
