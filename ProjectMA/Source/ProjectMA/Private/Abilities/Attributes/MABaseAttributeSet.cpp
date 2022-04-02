// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/Attributes/MABaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

UMABaseAttributeSet::UMABaseAttributeSet()
{
}

void UMABaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UMABaseAttributeSet, Stamina);
	
}

void UMABaseAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMABaseAttributeSet, MaxStamina, OldValue);
}

void UMABaseAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMABaseAttributeSet, Stamina, OldValue);
}
