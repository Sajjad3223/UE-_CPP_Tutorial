// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class CPP_TUTORIAL_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	void LookAtTarget(FVector TargetLocation);
	void Fire();
	
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* BarrelMesh;
	UPROPERTY(EditAnywhere,Category="Components")
	USceneComponent* ProjectileSpawnPoint;
	
	UPROPERTY(EditAnywhere,Category="Components")
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere,Category="Properties")
	float TurretRotationSpeed = 2;

	UPROPERTY(EditAnywhere,Category="Properties")
	TSubclassOf<class AProjectile> ProjectileClass;
	
};
