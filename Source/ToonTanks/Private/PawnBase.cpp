// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Components/HealthComponent.h"

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

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health Component"));
}

void APawnBase::RoatateTurret(FVector LookAtTarget)
{
	FVector LookAtTargetClean = FVector(FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z));
	FVector StartLocation = TurretMesh->GetComponentLocation();
	
	FRotator TurretRotation = FVector(LookAtTargetClean - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);

}

void APawnBase::Fire()
{
	if (ProjectileBlueprint)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		auto Projectile = GetWorld()->SpawnActor<AProjectileBase>(
			ProjectileBlueprint,
			SpawnLocation,
			SpawnRotation);
		Projectile->SetOwner(this);
	}

}

void APawnBase::HandleDestruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
}
