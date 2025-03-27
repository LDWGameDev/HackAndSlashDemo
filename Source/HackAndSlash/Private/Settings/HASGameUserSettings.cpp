// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/HASGameUserSettings.h"


UHASGameUserSettings* UHASGameUserSettings::Get()
{
	return Cast<UHASGameUserSettings>(GEngine->GetGameUserSettings());
}
