// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/HASBTSer_UpdateDistances.h"
#include <GameFramework/Actor.h>
#include <BehaviorTree/BlackboardComponent.h>



UHASBTSer_UpdateDistances::UHASBTSer_UpdateDistances(const FObjectInitializer& ObjectInitializer)
{
	DistanceKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UHASBTSer_UpdateDistances, DistanceKey));
	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UHASBTSer_UpdateDistances, TargetActorKey), AActor::StaticClass());
	SelfActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UHASBTSer_UpdateDistances, SelfActorKey), AActor::StaticClass());
}

void UHASBTSer_UpdateDistances::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		AActor* SelfActor = Cast<AActor>(BBComp->GetValueAsObject(SelfActorKey.SelectedKeyName));
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));

		if (SelfActor && TargetActor)
		{
			float Distance = FVector::Distance(SelfActor->GetActorLocation(), TargetActor->GetActorLocation());
			BBComp->SetValueAsFloat(DistanceKey.SelectedKeyName, Distance);
		}
	}
}
