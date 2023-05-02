// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectDammage.h"
#include "Engine.h"

void UDetectDammage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, TEXT("Coucou"));
}

void UDetectDammage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, TEXT("Salut"));
}

void UDetectDammage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Yellow, TEXT("Ciao"));
}