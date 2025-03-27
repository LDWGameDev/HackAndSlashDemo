// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HASAIController.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <BrainComponent.h>



void AHASAIController::BeginPlay()
{
	Super::BeginPlay();
	if (UBlackboardComponent* BBComp = GetBlackboardComponent())
	{
		BBComp->SetValueAsObject(PlayerActorKeyName, UGameplayStatics::GetPlayerPawn(this, 0));
	}
}

void AHASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (BTGraph)
	{
		RunBehaviorTree(BTGraph);
		if (UBlackboardComponent* BBComp = GetBlackboardComponent())
		{
			BBComp->SetValueAsObject(SelfActorKeyName, InPawn);
			BBComp->SetValueAsObject(PlayerActorKeyName, UGameplayStatics::GetPlayerPawn(this, 0));
		}
	}
}

void AHASAIController::SetZoneActor(AActor* ZoneActor)
{
	UBlackboardComponent* BBComp = GetBlackboardComponent();
	if (BBComp && ZoneActor)
	{
		BBComp->SetValueAsObject(ZoneActorKeyName, ZoneActor);
	}
}

void AHASAIController::StopBehaviorTree()
{
	if (UBrainComponent* BrainComp = GetBrainComponent())
	{
		BrainComp->StopLogic(TEXT("Dead"));
	}
}

