// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/HASCameraManagementComponent.h"

UHASCameraManagementComponent::UHASCameraManagementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHASCameraManagementComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UHASCameraManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

