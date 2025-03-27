// Fill out your copyright notice in the Description page of Project Settings.


#include "Systems/Zone/HASZone.h"
#include "Characters/Enemy/HASEnemyBase.h"

AHASZone::AHASZone()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHASZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHASZone::RegisterEnemy(AHASEnemyBase* NewEnemy)
{
	if (NewEnemy)
	{
		EnemyIds.AddUnique(NewEnemy->GetUniqueID());
		NewEnemy->OnDead.AddUObject(this, &ThisClass::HandleOnEnemyDead);
	}
}

void AHASZone::HandleOnEnemyDead(uint32 Id)
{
	EnemyIds.Remove(Id);
	if (EnemyIds.Num() == 0)
	{
		OnZoneCleared.Broadcast(GetUniqueID());
	}
}
