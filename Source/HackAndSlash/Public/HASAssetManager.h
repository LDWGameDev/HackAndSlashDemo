// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "HASAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class HACKANDSLASH_API UHASAssetManager : public UAssetManager
{
	GENERATED_BODY()

public: 
	virtual void StartInitialLoading() override;
};
