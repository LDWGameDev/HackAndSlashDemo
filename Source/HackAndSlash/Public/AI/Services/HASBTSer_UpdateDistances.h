// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HASBTSer_UpdateDistances.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASBTSer_UpdateDistances : public UBTService
{
	GENERATED_BODY()

public: 
	UHASBTSer_UpdateDistances(const FObjectInitializer& ObjectInitializer);

protected: 
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public: 
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector DistanceKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelfActorKey;
};
