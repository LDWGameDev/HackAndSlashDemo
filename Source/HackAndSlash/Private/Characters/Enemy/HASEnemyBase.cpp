// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy/HASEnemyBase.h"
#include "GAS/Attribute/HASEnemyAttributeSet.h"
#include <Components/WidgetComponent.h>
#include <GameplayEffectTypes.h>
#include <AbilitySystemComponent.h>
#include "GAS/HASAbilitySystemComponent.h"
#include "UI/HASGhostProgressBarWidget.h"
#include "AI/HASAIController.h"
#include "Systems/Zone/HASZone.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BlackboardComponent.h>

AHASEnemyBase::AHASEnemyBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	EnemyAttributeSet = CreateDefaultSubobject<UHASEnemyAttributeSet>(TEXT("Enemy Attribute Set"));
	HealthBarWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget Comp"));
	HealthBarWidgetComp->SetupAttachment(GetMesh());
	HealthBarWidgetComp->SetVisibility(false);
}

void AHASEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (AbilityComp && EnemyAttributeSet)
	{
		FOnGameplayAttributeValueChange& HealthChangeDelegate = AbilityComp->GetGameplayAttributeValueChangeDelegate(EnemyAttributeSet->GetCurrentHealthAttribute());
		HealthChangeDelegate.AddUObject(this, &ThisClass::HandleHealthAttributeChanged);
		if (UHASGhostProgressBarWidget* HealthBarWidget = Cast<UHASGhostProgressBarWidget>(HealthBarWidgetComp->GetWidget()))
		{
			HealthBarWidget->SetProgressBarValue(1.0f, true);
		}
	}

	if (IsNetStartupActor()) // Placed in level, not spawned at runtime
	{
		if (AHASAIController* AIController = GetController<AHASAIController>())
		{
			TArray<AActor*> ZoneActors;
			UGameplayStatics::GetAllActorsOfClass(this, AHASZone::StaticClass(), ZoneActors);

			if (ZoneActors.Num() > 0)
			{
				AActor* Closet = ZoneActors[0];
				float ClosetDistance = FVector::Distance(Closet->GetActorLocation(), GetActorLocation());

				for (int32 Iter = 1; Iter < ZoneActors.Num(); ++Iter)
				{
					float Distance = FVector::Distance(ZoneActors[Iter]->GetActorLocation(), GetActorLocation());
					if (Distance < ClosetDistance)
					{
						ClosetDistance = Distance;
						Closet = ZoneActors[Iter];
					}
				}

				AIController->SetZoneActor(Closet);

				if (AHASZone* AsZone = Cast<AHASZone>(Closet))
				{
					AsZone->RegisterEnemy(this);
				}
			}
		}
	}
}

void AHASEnemyBase::SetBlackboardIsGettingHitValue(bool Value)
{
	if (AHASAIController* AIController = GetController<AHASAIController>())
	{
		if (AIController->GetBlackboardComponent())
		{
			AIController->GetBlackboardComponent()->SetValueAsBool("GettingHit", Value);
		}
	}
}

void AHASEnemyBase::HandleHealthAttributeChanged(const FOnAttributeChangeData& ChangeData)
{
	if (HealthBarWidgetComp && EnemyAttributeSet)
	{
		if (ChangeData.NewValue != 0)
		{
			if (!HealthBarWidgetComp->IsVisible())
			{
				HealthBarWidgetComp->SetVisibility(true);
			}
			if (UHASGhostProgressBarWidget* HealthBarWidget = Cast<UHASGhostProgressBarWidget>(HealthBarWidgetComp->GetWidget()))
			{
				float NewProgressValue = ChangeData.NewValue / EnemyAttributeSet->GetMaxHealth();
				HealthBarWidget->SetProgressBarValue(NewProgressValue);
			}
		}
		else if (!IsDead())
		{
			Die();
		}
	}
}

void AHASEnemyBase::Die()
{
	Super::Die();
	if (HealthBarWidgetComp)
	{
		HealthBarWidgetComp->SetVisibility(false);
	}
	
	if (AHASAIController* AIController = GetController<AHASAIController>())
	{
		AIController->StopBehaviorTree();
	}
}
