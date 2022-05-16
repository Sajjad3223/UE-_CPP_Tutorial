// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_TUTORIAL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere,Category="Properties")
	USoundBase* ExplosionSound;
	UPROPERTY(EditAnywhere,Category="Properties")
	UParticleSystem* ExplosionEffect;
	
	UPROPERTY(EditAnywhere,Category="Properties")
	float DefaultHealth = 100;
	float CurrentHealth;
	bool IsDead = false;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor,float Damage,const UDamageType* DamageType,AController* Instigator,AActor* DamageCauser);
};
