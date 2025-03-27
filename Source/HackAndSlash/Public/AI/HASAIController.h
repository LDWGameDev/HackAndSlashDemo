// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HASAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API AHASAIController : public AAIController
{
	GENERATED_BODY()

protected: 
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

protected: 
	UPROPERTY(EditDefaultsOnly)
		TObjectPtr<UBehaviorTree> BTGraph;

	UPROPERTY(EditDefaultsOnly)
		FName SelfActorKeyName = "SelfActor";

	UPROPERTY(EditDefaultsOnly)
		FName PlayerActorKeyName = "PlayerActor";

	UPROPERTY(EditDefaultsOnly)
		FName ZoneActorKeyName = "ZoneActor";

public:
	void SetZoneActor(AActor* ZoneActor);
	void StopBehaviorTree();
};
