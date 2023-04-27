// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sword.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ZeldaBOTW/ZeldaBOTWCharacter.h"
#include "Engine/EngineTypes.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Epee"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));

	//Basic var
	Dammage = 10;
	Durability = 10;
	RootComponent = Collision;

	//SetupMesh
	Mesh->USceneComponent::SetupAttachment(RootComponent);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetRelativeLocation(FVector(0, 0, -33));

	//SetupCollisionCapsule
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCapsuleRadius(20);
	Collision->SetCapsuleHalfHeight(33);

	this->SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay(); 
	Collision->SetSimulatePhysics(false);
	//Collision->SetSimulatePhysics(true);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASword::BeginOverlap);
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ASword::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AZeldaBOTWCharacter* Player = Cast<AZeldaBOTWCharacter>(OtherActor);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Collision")));
	if (Player && (Player->isHoldingWeapon == false)) {
		Player->isHoldingWeapon = true;
		Player->Epee->SetStaticMesh(Mesh->GetStaticMesh());
		Player->DammageToDeal = Dammage;
		Player->DurabilityInSword = Durability;
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("I Have weapon")));
	}
}

