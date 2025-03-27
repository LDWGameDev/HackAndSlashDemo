// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/HASPlayerAnimInstance.h"
#include "Characters/Player/HASPlayerCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

UHASPlayerAnimInstance::UHASPlayerAnimInstance()
{

}

void UHASPlayerAnimInstance::NativeBeginPlay()
{
	OwnerChar = Cast<AHASPlayerCharacter>(TryGetPawnOwner());
}

void UHASPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerChar) return;
	
	FVector2D ComputedMovementInputSpeed = OwnerChar->GetComputedMovementInputSpeed();
	ForwardDirectionValue = ComputedMovementInputSpeed.Y;
	RightDirectionValue = ComputedMovementInputSpeed.X;

	if (UCharacterMovementComponent* OwnerMoveComp = OwnerChar->GetCharacterMovement())
	{
		bFalling = OwnerMoveComp->IsFalling();
	}
}
