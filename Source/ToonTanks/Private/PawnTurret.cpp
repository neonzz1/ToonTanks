// ©Neonzz Games©


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::CheckFireCondition()
{
	
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}