// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/HASZoneGS.h"
#include <Kismet/GameplayStatics.h>
#include "Systems/Zone/HASZone.h"

AHASZoneGS::AHASZoneGS()
{
		
}

bool AHASZoneGS::HasMatchStarted() const 
{
	return bAllZoneCleared;
}

bool AHASZoneGS::HasMatchEnded() const
{
	return bAllZoneCleared;
}

void AHASZoneGS::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ZoneActors;
	UGameplayStatics::GetAllActorsOfClass(this, AHASZone::StaticClass(), ZoneActors);
	for (AActor* ActorIter : ZoneActors)
	{
		if (AHASZone* Zone = Cast<AHASZone>(ActorIter))
		{
			Zone->OnZoneCleared.AddUObject(this, &ThisClass::HandleOnZoneCleared);
			ZoneIds.AddUnique(Zone->GetUniqueID());
		}
	}
}

void AHASZoneGS::HandleOnZoneCleared(uint32 ZoneId)
{
	ZoneIds.Remove(ZoneId);
	if (ZoneIds.Num() == 0)
	{
		Win();
	}
}

void AHASZoneGS::Win()
{
	OnWon.Broadcast();
}

void AHASZoneGS::Lose()
{
	OnLost.Broadcast();
}
