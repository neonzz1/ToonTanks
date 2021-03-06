// ©Neonzz Games©


#include "TankGameModeBase.h"
#include "PawnTank.h"
#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Controllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), FoundActors);

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), FoundActors);

	return FoundActors.Num();
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate FTimerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
			&APlayerControllerBase::SetPlayerEnabledState, true);

		auto PlayerEnableDelay = FMath::RoundToFloat(StartDelay);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, FTimerEnableDelegate, PlayerEnableDelay, false);
	}

	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool bPlayerWon)
{
	UE_LOG(LogTemp, Warning, TEXT("A Pawn Has Died"))
	GameOver(bPlayerWon);
}

