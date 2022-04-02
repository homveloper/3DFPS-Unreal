// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EMAAbilityInput.h"
#include "UObject/Object.h"
#include "MAGameplayAbilitiy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMA_API UMAGameplayAbilitiy : public UObject
{
	GENERATED_BODY()

public:
	UMAGameplayAbilitiy();

	// 어빌리티는 특정 입력이 있을때 발동
	EMAAbilityInput	AbilityInput{EMAAbilityInput::EAI_None};
};
