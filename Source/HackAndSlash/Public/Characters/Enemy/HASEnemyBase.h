// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../HASCharacterBase.h"
#include <GameplayEffectTypes.h>
#include "HASEnemyBase.generated.h"


class UHASEnemyAttributeSet;
class UWidgetComponent;

UCLASS()
class HACKANDSLASH_API AHASEnemyBase : public AHASCharacterBase
{
	GENERATED_BODY()

public:
	AHASEnemyBase(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public: 
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	TObjectPtr<UHASEnemyAttributeSet> EnemyAttributeSet;

protected: 
	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> HealthBarWidgetComp;

public: 
	UFUNCTION(BlueprintCallable)
	void SetBlackboardIsGettingHitValue(bool Value);

protected: 
	void HandleHealthAttributeChanged(const FOnAttributeChangeData& ChangeData);
	virtual void Die() override;
};
