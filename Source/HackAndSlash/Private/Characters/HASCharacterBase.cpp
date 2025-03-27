// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HASCharacterBase.h"
#include "GAS/HASAbilitySystemComponent.h"
#include <MotionWarpingComponent.h>
#include <AbilitySystemBlueprintLibrary.h>
#include "HASGameplayTags.h"
#include <Engine/EngineTypes.h>
#include <Components/CapsuleComponent.h>

AHASCharacterBase::AHASCharacterBase(const FObjectInitializer& ObjectInitilizer)
{
	PrimaryActorTick.bCanEverTick = true;

	AbilityComp = CreateDefaultSubobject<UHASAbilitySystemComponent>("Ability System Component");
	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>("Motion Warping Component");
}

void AHASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilityComp)
	{
		AbilityComp->InitAbilityActorInfo(this, this);
		AbilityComp->ApplyDefaultGEs();
		AbilityComp->GrantDefaultAbilities();
	}
}

void AHASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AHASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilityComp;
}

bool AHASCharacterBase::IsDead() const
{
	return (AbilityComp && AbilityComp->HasMatchingGameplayTag(FHASGameplayTags::Get().State_Dead));
}

void AHASCharacterBase::Die()
{
	OnDead.Broadcast(GetUniqueID());

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, FHASGameplayTags::Get().State_Dead, FGameplayEventData());
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionProfileName("Ragdoll", false);
	GetMesh()->SetSimulatePhysics(true);
}