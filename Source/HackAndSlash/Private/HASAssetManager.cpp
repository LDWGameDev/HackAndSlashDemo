// Fill out your copyright notice in the Description page of Project Settings.


#include "HASAssetManager.h"
#include "HASGameplayTags.h"

void UHASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FHASGameplayTags::Get().InitAllTags();
}
