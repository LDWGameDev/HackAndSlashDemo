// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/HASComboAbility.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Characters/HASCharacterBase.h"
#include <RootMotionModifier.h>
#include <MotionWarpingComponent.h>
#include "Characters/Enemy/HASEnemyBase.h"
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "HASPlayerStatusSubsystem.h"

void UHASComboAbility::PerformHitTrace(int32 HitTraceId, TArray<FHitResult>& OutHitResults)
{
	RecentHitActors.Empty();
	for (FHASHitTrace& TraceIter : HitTraces)
	{
		if (TraceIter.Id != HitTraceId) continue;
		
		OutHitResults.Empty();
		for (FHASSphereTraceObjects& SphereTraceIter : TraceIter.ObjectSphereTraces)
		{
			AActor* AvatarActor = GetAvatarActorFromActorInfo();
			if (!AvatarActor) return;

			FVector TraceStartWorld = AvatarActor->GetActorTransform().TransformPosition(SphereTraceIter.TraceStart);
			FVector TraceEndWorld = AvatarActor->GetActorTransform().TransformPosition(SphereTraceIter.TraceEnd);

			TArray<AActor*> IgnoreActors;
			IgnoreActors.Add(AvatarActor);

			TArray<FHitResult> Results;

			UKismetSystemLibrary::SphereTraceMultiForObjects(
				AvatarActor, 
				TraceStartWorld,
				TraceEndWorld, 
				SphereTraceIter.Radius, 
				SphereTraceIter.ObjectTypes, 
				false, 
				IgnoreActors,
				(bDebugHitTrace ? EDrawDebugTrace::Type::ForDuration : EDrawDebugTrace::Type::None),
				Results, 
				true
			);

			auto ExistHitActor = [&](const FHitResult& Hit, const TArray<FHitResult>& HitArray) {
				for (auto& HitIter : HitArray)
				{
					if (HitIter.GetActor() == Hit.GetActor())
					{
						return true;
					}
				}
				return false;
			};

			for (FHitResult& HitResultIter : Results)
			{
				if (!ExistHitActor(HitResultIter, OutHitResults))
				{
					OutHitResults.Add(HitResultIter);
					RecentHitActors.Add(HitResultIter.GetActor());
				}
			}
		}
	}

	if (OutHitResults.Num() > 0)
	{
		UHASPlayerStatusSubsystem::Get(this)->IncrementComboCounter();
	}
}

AActor* UHASComboAbility::SetWarpingTargetToClosetActor(FName TargetName, FVector LocalOffsetLocation, FRotator LocalOffsetRotation, float Range /*= 300.0f*/)
{
	AActor* ClosetActor = FindClosetTargetInRange(Range);
	AHASCharacterBase* AvatarChar = Cast<AHASCharacterBase>(GetAvatarActorFromActorInfo());

	if (AvatarChar && AvatarChar->GetMotionWarpingComp())
	{
		if (ClosetActor)
		{
			FTransform TargetTransform = ClosetActor->GetActorTransform();
			FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AvatarChar->GetActorLocation(), ClosetActor->GetActorLocation());
			LookAtRotation.Pitch = 0.0f;
			LookAtRotation.Roll = 0.0f;
			TargetTransform.SetRotation(LookAtRotation.Quaternion());

			FTransform WarpTransform;
			WarpTransform.SetLocation(TargetTransform.TransformPosition(LocalOffsetLocation));
			WarpTransform.SetRotation(TargetTransform.TransformRotation(LocalOffsetRotation.Quaternion()));

			FMotionWarpingTarget WarpTarget(TargetName, WarpTransform);
			AvatarChar->GetMotionWarpingComp()->AddOrUpdateWarpTarget(WarpTarget);
		}
		else
		{
			AvatarChar->GetMotionWarpingComp()->RemoveWarpTarget(TargetName);
		}
	}
	return ClosetActor;
}

void UHASComboAbility::SetWarpingToRecentHitActors(FName TargetName, FVector LocalOffsetLocation, FRotator LocalOffsetRotation)
{
	AHASCharacterBase* AvatarChar = Cast<AHASCharacterBase>(GetAvatarActorFromActorInfo());
	if (AvatarChar && AvatarChar->GetMotionWarpingComp())
	{
		for (AActor* ActorIter : RecentHitActors)
		{
			if (!ActorIter || !IsValidTarget(ActorIter)) continue;

			if (ActorIter)
			{
				FTransform TargetTransform = ActorIter->GetActorTransform();
				FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(AvatarChar->GetActorLocation(), ActorIter->GetActorLocation());
				LookAtRotation.Pitch = 0.0f;
				LookAtRotation.Roll = 0.0f;
				TargetTransform.SetRotation(LookAtRotation.Quaternion());

				FTransform WarpTransform;
				WarpTransform.SetLocation(TargetTransform.TransformPosition(LocalOffsetLocation));
				WarpTransform.SetRotation(TargetTransform.TransformRotation(LocalOffsetRotation.Quaternion()));

				FMotionWarpingTarget WarpTarget(TargetName, WarpTransform);
				AvatarChar->GetMotionWarpingComp()->AddOrUpdateWarpTarget(WarpTarget);
			}
			else
			{
				AvatarChar->GetMotionWarpingComp()->RemoveWarpTarget(TargetName);
			}

			break;
		}
	}
}

void UHASComboAbility::SetWarpingToLocalOffset(FName TargetName, FVector LocalOffsetLocation)
{
	AHASCharacterBase* AvatarChar = Cast<AHASCharacterBase>(GetAvatarActorFromActorInfo());
	if (AvatarChar && AvatarChar->GetMotionWarpingComp())
	{
		FTransform TargetTransform = AvatarChar->GetActorTransform();
		FTransform WarpTransform;
		WarpTransform.SetLocation(TargetTransform.TransformPosition(LocalOffsetLocation));

		FMotionWarpingTarget WarpTarget(TargetName, WarpTransform);
		AvatarChar->GetMotionWarpingComp()->AddOrUpdateWarpTarget(WarpTarget);
	}
}

AActor* UHASComboAbility::FindClosetTargetInRange(float Range /*= 300.0f*/)
{
	if (AActor* AvatarActor = GetAvatarActorFromActorInfo())
	{
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
		TArray<AActor*> IgnoreActors;
		TArray<AActor*> OutActors;
		UKismetSystemLibrary::SphereOverlapActors(AvatarActor, AvatarActor->GetActorLocation(), Range, ObjectTypes, AHASEnemyBase::StaticClass(), IgnoreActors, OutActors);

		TArray<AActor*> AliveActors;
		for (AActor* ActorIter : OutActors)
		{
			if (IsValidTarget(ActorIter))
			{
				AliveActors.Add(ActorIter);
			}
		}

		if (AliveActors.Num() > 0)
		{
			AActor* ClosetActor = AliveActors[0];
			float MinDistance = FVector::Distance(ClosetActor->GetActorLocation(), AvatarActor->GetActorLocation());

			for (int32 Iter = 1; Iter < AliveActors.Num(); ++Iter)
			{
				float Distance = FVector::Distance(AliveActors[Iter]->GetActorLocation(), AvatarActor->GetActorLocation());
				if (Distance < MinDistance)
				{
					MinDistance = Distance;
					ClosetActor = AliveActors[Iter];
				}
			}
			return ClosetActor;
		}
	}
	return nullptr;
}

void UHASComboAbility::SetTargetGetHitWarpingTarget(AActor* Target, FName GetHitWarpingTargetName, FVector OffsetPosition, FRotator OffsetRotation)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	AHASCharacterBase* TargetAsBase = Cast<AHASCharacterBase>(Target);
	if (TargetAsBase && TargetAsBase->GetMotionWarpingComp() && AvatarActor)
	{
		FTransform TargetTransform;
		TargetTransform.SetLocation(TargetAsBase->GetActorLocation());

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(TargetAsBase->GetActorLocation(), AvatarActor->GetActorLocation());
		LookAtRotation.Pitch = 0.0f;
		LookAtRotation.Roll = 0.0f;
		TargetTransform.SetRotation(LookAtRotation.Quaternion());

		FTransform WarpTransform;
		WarpTransform.SetLocation(TargetTransform.TransformPosition(OffsetPosition));
		WarpTransform.SetRotation(TargetTransform.TransformRotation(OffsetRotation.Quaternion()));

		FMotionWarpingTarget WarpTarget(GetHitWarpingTargetName, WarpTransform);
		TargetAsBase->GetMotionWarpingComp()->AddOrUpdateWarpTarget(WarpTarget);
	}
}

void UHASComboAbility::SetAvatarActorMovementMode(EMovementMode NewMovementMode)
{
	if (AHASCharacterBase* AvatarCharacter = Cast<AHASCharacterBase>(GetAvatarActorFromActorInfo()))
	{
		AvatarCharacter->GetCharacterMovement()->SetMovementMode(NewMovementMode);
	}
}

bool UHASComboAbility::IsValidTarget(AActor* Actor)
{
	AHASCharacterBase* BaseChar = Cast<AHASCharacterBase>(Actor);
	return (BaseChar && !BaseChar->IsDead());
}

bool UHASComboAbility::IsValidRecentHitActors()
{
	for (AActor* ActorIter : RecentHitActors)
	{
		if (IsValidTarget(ActorIter))
		{
			return true;
		}
	}
	return false;
}

