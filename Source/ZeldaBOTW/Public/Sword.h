// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "Sword.generated.h"

UCLASS()
class ZELDABOTW_API ASword : public AActor
{
		GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* Collision;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* Projectile;



	
public:	
	// Sets default values for this actor's properties
	ASword();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float Dammage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default, meta = (AllowPrivateAccess = "true"))
	float Durabily;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
