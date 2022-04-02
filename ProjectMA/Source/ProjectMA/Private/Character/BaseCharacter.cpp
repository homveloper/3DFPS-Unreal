// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"

#include "EMAAbilityInput.h"
#include "Abilities/MAGameplayAbilitiy.h"
#include "Abilities/Attributes/MABaseAttributeSet.h"
#include "Components/MAAbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	bAbilitiesInitialized = false;

	AbilitySystemComponent = CreateDefaultSubobject<UMAAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);	// 싱글 플레이 고려

	AttributeSet = CreateDefaultSubobject<UMABaseAttributeSet>(TEXT("AttributeSet"));	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// 서버 GAS 초기화
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}		
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this,this);

	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"EAI_Confirm",
			"EAI_Cancel",
			"EMAAbilityInput",
			static_cast<int32>(EMAAbilityInput::EAI_Confirm),
			static_cast<int32>(EMAAbilityInput::EAI_Cancel));

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds(
			"EAI_Confirm",
			"EAI_Cancel",
			"EMAAbilityInput",
			static_cast<int32>(EMAAbilityInput::EAI_Confirm),
			static_cast<int32>(EMAAbilityInput::EAI_Cancel));

		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::AddInitGameplayAbilities()
{
	check(AbilitySystemComponent);

	if(GetLocalRole() == ROLE_Authority && !bAbilitiesInitialized)
	{
		// 서버에서만 어빌리티를 부여
		for(TSubclassOf<UMAGameplayAbilitiy>& ability : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(
				static_cast<TSubclassOf<UGameplayAbility>>(ability), 1,
				static_cast<int32>(ability.GetDefaultObject()->AbilityInput),
				this));
		}
		
		// 패시브 적용
		for(const TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(
				GameplayEffect, 1, EffectContext);

			if(NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(
					*NewHandle.Data.Get()(), AbilitySystemComponent
				);
			}
		}
		
		bAbilitiesInitialized = true;
	}
}
