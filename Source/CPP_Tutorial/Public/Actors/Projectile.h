// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class CPP_TUTORIAL_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(EditAnywhere,Category="Components")
	class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere,Category="Components")
	USoundBase* FireSound;
	UPROPERTY(EditAnywhere,Category="Components")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere,Category="Properties")
	float Damage = 20;

	UPROPERTY(EditAnywhere,Category="Properties")
	TSubclassOf< UDamageType > DamageType;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
