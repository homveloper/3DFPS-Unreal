// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "Character/ALSBaseCharacter.h"
#include "BaseCharacter.generated.h"


class UMAGameplayAbilitiy;
class UMAAbilitySystemComponent;
class UMABaseAttributeSet;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTMA_API ABaseCharacter : public AALSBaseCharacter, public IAbilitySystemInterface 
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/****************
	 * Ability System
	 * **************/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void AddInitGameplayAbilities();

	/**
	 * @brief 캐릭터가 데미지를 받거나, 죽을 때 호출됨
	 * @param DamageAmount 
	 * @param HitInfo 
	 * @param DamageTags 
	 * @param InstigatorchCharacter 
	 * @param DamageCauser 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags,
		ABaseCharacter* InstigatorchCharacter, AActor* DamageCauser);

	
	/**
	 * @brief 어떤 버프 & 디버프나 물약과 같은 효과로 인해 스태미나가 변할때 호출됨
	 * @param DeltaValue 
	 * @param EventTags 
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnStaminaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	
protected:
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MA|Abilities", meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MA|Abilities", meta=(AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UMAGameplayAbilitiy>> GameplayAbilities;

	UPROPERTY()
	uint8 bAbilitiesInitialized:1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MA|Components", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMAAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MA|Attributes", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UMABaseAttributeSet> AttributeSet;
	
};
