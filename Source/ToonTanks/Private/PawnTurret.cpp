// ©Neonzz Games©


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) { return; }
	
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		Fire();
		UE_LOG(LogTemp, Warning, TEXT("CHECKFIRECON"));
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn) 
	{ 
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }

	FVector PlayerTankLocation = PlayerPawn->GetActorLocation();

	RoatateTurret(PlayerTankLocation);

}