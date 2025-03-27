// Fill out your copyright notice in the Description page of Project Settings.


#include "HASGameplayTags.h"
#include <GameplayTagsManager.h>

void FHASGameplayTags::InitAllTags()
{
	AddTag(InputTag_CursorDelta, "Input.CursorDelta", TEXT("Cursor delta input tag"));
	AddTag(InputTag_Movement, "Input.Movement", TEXT("Movement input tag"));
	AddTag(InputTag_LightAttack, "Input.LightAttack", TEXT("Light Attack input tag"));
	AddTag(InputTag_HeavyAttack, "Input.HeavyAttack", TEXT("Heavy Attack input tag"));
	AddTag(InputTag_Jump, "Input.Jump", TEXT("Jump input tag"));
	AddTag(InputTag_Dodge, "Input.Dodge", TEXT("Dodge input tag"));
	AddTag(InputTag_Sprint, "Input.Sprint", TEXT("Sprint input tag"));

	AddTag(Action_Sprint, "Action.Sprint", TEXT("Sprint action tag"));
	AddTag(Action_Jump, "Action.Jump", TEXT("Jump action tag"));
	AddTag(Action_Fall, "Action.Fall", TEXT("Fall action tag"));
	AddTag(Action_GroundAttack, "Action.Attack.GroundAttack", TEXT("Ground Attack action tag"));
	AddTag(Action_AirAttack, "Action.Attack.AirAttack", TEXT("Air Attack action tag"));
	AddTag(Action_ReceiveLightAttack, "Action.ReceiveAttack.LightAttack", TEXT("Receive Light Attack action tag"));
	AddTag(Action_ReceiveHeavyAttack, "Action.ReceiveAttack.HeavyAttack", TEXT("Receive Heavy Attack action tag"));
	AddTag(Action_ReceiveKnockup, "Action.ReceiveAttack.Knockup", TEXT("Receive Knockup action tag"));
	AddTag(Action_ReceiveKnockdown, "Action.ReceiveAttack.Knockdown", TEXT("Receive Knockdown action tag"));
	AddTag(Action_ReceiveKnockback, "Action.ReceiveAttack.Knockback", TEXT("Receive Knockback action tag"));

	AddTag(State_CanDoNextCombo, "State.CanDoNextCombo", TEXT("Can do next combo state tag"));
	AddTag(State_Dead, "State.Dead", TEXT("Dead state tag"));
	AddTag(Stat_StaminaConsumption, "Stat.StaminaConsumption", TEXT("Stamina Consumption stat tag"));

	AddTag(GC_Poison, "GameplayCue.Poison", TEXT("Poison GC tag"));

}

void FHASGameplayTags::AddTag(FGameplayTag& Tag, const FName& TagContent, const FString& TagDescription /*= TEXT("")*/)
{
	Tag = UGameplayTagsManager::Get().AddNativeGameplayTag(TagContent, TagDescription);
}
