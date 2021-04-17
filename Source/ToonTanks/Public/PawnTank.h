// ©Neonzz Games©

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerController;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
public:

	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

private:
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	FVector MoveDirection;
	FQuat RotationDirection;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))// maybe use EditAnywhere
	float MoveSpeed = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))// maybe use EditAnywhere
	float RotateSpeed = 100.f;

	APlayerController* PlayerControllerRef;

	bool bIsPlayerAlive = true;

	void CalulateMoveInput(float Throttle);
	void CalculateRotateInput(float Throttle);

	void Move();
	void Rotate();
};
