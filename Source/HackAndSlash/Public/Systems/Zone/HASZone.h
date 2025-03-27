// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HASZone.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnZoneCleared, uint32);

class AHASEnemyBase;

UCLASS()
class HACKANDSLASH_API AHASZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AHASZone();

protected:
	virtual void BeginPlay() override;

public: 
	FOnZoneCleared OnZoneCleared;
	
protected: 
	UPROPERTY()
	TArray<uint32> EnemyIds;

public: 
	void RegisterEnemy(AHASEnemyBase* NewEnemy);

private: 
	void HandleOnEnemyDead(uint32 Id);
};
