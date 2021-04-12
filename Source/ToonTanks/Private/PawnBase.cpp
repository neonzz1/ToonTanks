// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule Comp"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Base Mesh"));
	BaseMesh->AttachToComponent(CapsuleComp, FAttachmentTransformRules::KeepWorldTransform);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Turret Mesh"));
	TurretMesh->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepWorldTransform);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepWorldTransform);
}


