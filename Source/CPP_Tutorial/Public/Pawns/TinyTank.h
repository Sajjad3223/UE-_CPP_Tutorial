// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "TinyTank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged,float,Health);

UCLASS()
class CPP_TUTORIAL_API ATinyTank : public APawnBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATinyTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	
	
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnRight(float Value);

	UPROPERTY(EditAnywhere,Category="Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere,Category="Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere,Category="Components")
	class UFloatingPawnMovement* PawnMovement;

	UPROPERTY(EditAnywhere,Category="Properties")
	float BodyRotationSpeed = 60;
	
};
