// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HASGameplayAbility.h"
#include <Engine/EngineTypes.h>
#include "HASComboAbility.generated.h"

USTRUCT(BlueprintType)
struct FHASSphereTraceObjects
{
	GENERATED_BODY()

	FHASSphereTraceObjects() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TraceStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector TraceEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
};

USTRUCT(BlueprintType)
struct FHASHitTrace
{
	GENERATED_BODY()

	FHASHitTrace() { }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHASSphereTraceObjects> ObjectSphereTraces;
};

USTRUCT(BlueprintType)
struct FHASHitTraceEvent
{
	GENERATED_BODY()

	FHASHitTraceEvent() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Event;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TraceId;
};

UENUM(BlueprintType)
enum class EHASCombatWarpingType : uint8
{
	None				UMETA(DisplayName = "None"),
	ClosetTarget		UMETA(DisplayName = "Closet Target"),
	RecentHit			UMETA(DisplayName = "Recent Hit"),
	RecentOrCloset		UMETA(DisplayName = "Recent Hit or Closet Target"), // If not found recent hit target then fallback to closet target
	LocalOffset			UMETA(DisplayName = "Local Offset")
};

/**
 * s
 */
UCLASS()
class HACKANDSLASH_API UHASComboAbility : public UHASGameplayAbility
{
	GENERATED_BODY()
	
protected: 
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TArray<FHASHitTrace> HitTraces;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool bDebugHitTrace = false;

	UPROPERTY(BlueprintReadWrite, Category = "Damage")
	TArray<AActor*> RecentHitActors;		

protected: 
	UFUNCTION(BlueprintCallable)
	void PerformHitTrace(int32 HitTraceId, TArray<FHitResult>& OutHitResults);

	UFUNCTION(BlueprintCallable)
	AActor* SetWarpingTargetToClosetActor(FName TargetName, FVector LocalOffsetLocation, FRotator LocalOffsetRotation, float Range = 300.0f);

	UFUNCTION(BlueprintCallable)
	void SetWarpingToRecentHitActors(FName TargetName, FVector LocalOffsetLocation, FRotator LocalOffsetRotation);

	UFUNCTION(BlueprintCallable)
	void SetWarpingToLocalOffset(FName TargetName, FVector LocalOffsetLocation);

	UFUNCTION(BlueprintCallable)
	AActor* FindClosetTargetInRange(float Range = 300.0f);

	UFUNCTION(BlueprintCallable)
	void SetTargetGetHitWarpingTarget(AActor* Target, FName GetHitWarpingTargetName, FVector OffsetPosition, FRotator OffsetRotation);

	UFUNCTION(BlueprintCallable)
	void SetAvatarActorMovementMode(EMovementMode NewMovementMode);

	bool IsValidTarget(AActor* Actor);

	UFUNCTION(BlueprintPure)
	bool IsValidRecentHitActors();
};

