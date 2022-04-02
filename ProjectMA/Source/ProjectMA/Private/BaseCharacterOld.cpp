// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterOld.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseCharacterOld::ABaseCharacterOld():
	// 카메라 변수
	SocketOffset(0.f,50.f,0.f),
	TargetArmLength(300),

	// 마우스 조준 & 비조준 회전 민감도
	HipHorizontalRate(1.f),
	HipVerticalRate(1.f),
	AimingHorizontalRate(0.2f),
	AimingVerticalRate(0.2f),
	bIsAiming(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 스프링암 컴포넌트
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);	
	SpringArm->TargetArmLength = TargetArmLength;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = SocketOffset;
	
	// TPS 카메라
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);		// 스프링암에 카메라를 부착
	FollowCamera->bUsePawnControlRotation = false;									// 스프링암에 대해 카메라 회전 금지

	// 컨트롤러가 회전할 때 회전을 금지, 컨트롤러가 오직 카메라에만 영향을 받도록 설정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Character Movement 설정
	GetCharacterMovement()->bOrientRotationToMovement = false;	// 입력 방향에 따라 캐릭터가 움직이도록 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void ABaseCharacterOld::PrimaryButtonPressed()
{
	bPrimaryButtonPressed = true;
	FireWeapon();
}

void ABaseCharacterOld::PrimaryButtonReleased()
{
	bPrimaryButtonPressed = false;
}

void ABaseCharacterOld::SecondaryButtonPressed()
{
	bSecondaryButtonPressed = true;
	bIsAiming = true;
}

void ABaseCharacterOld::SecondaryButtonReleased()
{
	bSecondaryButtonPressed = false;
	bIsAiming = false;
}

// Called when the game starts or when spawned
void ABaseCharacterOld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacterOld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacterOld::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveVertical", this, &ABaseCharacterOld::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ABaseCharacterOld::MoveHorizontal);
	
	PlayerInputComponent->BindAxis("TurnHorizontal", this, &ABaseCharacterOld::TurnHorizontal);
	PlayerInputComponent->BindAxis("TurnVertical", this, &ABaseCharacterOld::TurnVertical);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("PrimaryButton", IE_Pressed, this, &ABaseCharacterOld::PrimaryButtonPressed);
	PlayerInputComponent->BindAction("PrimaryButton", IE_Released, this, &ABaseCharacterOld::PrimaryButtonPressed);

	PlayerInputComponent->BindAction("SecondaryButton", IE_Pressed, this, &ABaseCharacterOld::SecondaryButtonPressed);
	PlayerInputComponent->BindAction("SecondaryButton", IE_Released, this, &ABaseCharacterOld::SecondaryButtonReleased);
}

void ABaseCharacterOld::MoveVertical(float Value)
{
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::X), Value);	
}

void ABaseCharacterOld::MoveHorizontal(float Value)
{
	AddMovementInput(FRotationMatrix(Controller->GetControlRotation()).GetUnitAxis(EAxis::Y), Value);	
}

void ABaseCharacterOld::TurnVertical(float Value)
{
	AddControllerPitchInput(Value * (bIsAiming ? AimingHorizontalRate : HipHorizontalRate));
}
void ABaseCharacterOld::TurnHorizontal(float Value)
{
	AddControllerYawInput(Value * (bIsAiming ? AimingHorizontalRate : HipHorizontalRate));
}


void ABaseCharacterOld::FireWeapon()
{
	
}

void ABaseCharacterOld::EquipWeapon()
{
}

void ABaseCharacterOld::DropWeapon()
{
}

