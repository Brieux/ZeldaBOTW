// Copyright Epic Games, Inc. All Rights Reserved.

#include "ZeldaBOTWCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Misc/App.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AZeldaBOTWCharacter

AZeldaBOTWCharacter::AZeldaBOTWCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	isHoldingWeapon = false;
	DammageToDeal;
	DurabilityInSword;
	AnimToPlayCombo01;
	AnimToPlayCombo02;
	AnimToPlayCombo03;
	AnimToPlayCombo04;
	AnimToPlayCombo05;
	AnimToPlayCombo06;
	ComboUsed;
	indexToPlay = 0;
	CantAttack = false;
	CanMove = true;
	ComboToChoose = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/_Global/Characters/Mannequin_UE4/Meshes/SKM_UE4.SKM_UE4'"));
	GetMesh()->SetSkeletalMesh(MeshAsset.Object,false);


	//Sword Apply
	Epee = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Epee"));
	Epee->SetupAttachment(GetMesh(), TEXT("SwordHolder"));

	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = 0;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AZeldaBOTWCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Epee->SetupAttachment(GetMesh(), TEXT("SwordHolder"));
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AZeldaBOTWCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AZeldaBOTWCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AZeldaBOTWCharacter::Look);

		//Use Weapon
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AZeldaBOTWCharacter::Attack);

	}

}

void AZeldaBOTWCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && CanMove)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		//SpeedForward = SpeedForward + (FApp::GetDeltaTime() * 50);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AZeldaBOTWCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AZeldaBOTWCharacter::Attack(void)
{
	if (isHoldingWeapon && (CantAttack == false)) {

		//ChooseComboToPerform
		if (ComboToChoose == true) {
			ComboToChoose = false;
			int chooseComboInt = FMath::RandRange(0, 5);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Combo to perform %d"), chooseComboInt));
			switch(chooseComboInt) {
				case (0):
					ComboUsed = AnimToPlayCombo01;
					break;
				case (1):
					ComboUsed = AnimToPlayCombo02;
					break;
				case (2):
					ComboUsed = AnimToPlayCombo03;
					break;
				case (3):
					ComboUsed = AnimToPlayCombo04;
					break;
				case (4):
					ComboUsed = AnimToPlayCombo05;
					break;
				case (5):
					ComboUsed = AnimToPlayCombo06;
					break;
				default:
					ComboUsed = AnimToPlayCombo01;
					break;
			}
				
		}
		//PlayMontage
		GetMesh()->GetAnimInstance()->Montage_Play(ComboUsed[indexToPlay],1.f, EMontagePlayReturnType::Duration,0.f,true);
		
		//BlockInput
		CantAttack = true;
		CanMove = false;

		//DelegateOnBlendOut
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUFunction(this, TEXT("AllowAttackAndMove"));
		GetMesh()->GetAnimInstance()->Montage_SetBlendingOutDelegate(EndDelegate);
		

	}
}

void AZeldaBOTWCharacter::AllowAttackAndMove() {
	CantAttack = false;
	CanMove = true;
	indexToPlay += 1;
	if (indexToPlay == ComboUsed.Num()) {
		indexToPlay = 0;
		ComboToChoose = true;
	}
}




