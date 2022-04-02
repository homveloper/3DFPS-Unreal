// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacterOld.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROJECTMA_API ABaseCharacterOld : public ACharacter
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Sets default values for this character's properties
	ABaseCharacterOld();
	
protected:
	void PrimaryButtonPressed();
	void PrimaryButtonReleased();
	
	void SecondaryButtonPressed();
	void SecondaryButtonReleased();
	
private:
	void MoveVertical(float Value);
	void MoveHorizontal(float Value);
	void TurnVertical(float Value);
	void TurnHorizontal(float Value);

	void SetLookSensitivity();
	void CameraInterpZoom();

	void FireWeapon();
	void EquipWeapon();
	void DropWeapon();
private:
	// 3인칭 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	FVector SocketOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	float TargetArmLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	float HipHorizontalRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	float HipVerticalRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	float AimingHorizontalRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta=(AllowPrivateAccess = "true"))
	float AimingVerticalRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess = "true"))
	bool bIsAiming;
	bool bPrimaryButtonPressed;
	bool bSecondaryButtonPressed;
};
