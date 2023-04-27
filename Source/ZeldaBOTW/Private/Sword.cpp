// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values
ASword::ASword()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Epee"));
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	Dammage = 10;
	Durabily = 10;
	RootComponent = Collision;
	Mesh->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

