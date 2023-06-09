// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Components/StaticMeshComponent.h"
#include "ZeldaBOTWCharacter.generated.h"


UCLASS(config=Game)
class AZeldaBOTWCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	


public:
	AZeldaBOTWCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	bool isHoldingWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Epee;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		float DammageToDeal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		float DurabilityInSword;

	bool ComboToChoose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo04;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo05;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> AnimToPlayCombo06;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*> ComboUsed;

	int indexToPlay;

	bool CantAttack;
	bool CanMove;

	UFUNCTION()
		void AllowAttackAndMove();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Attack(void);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

