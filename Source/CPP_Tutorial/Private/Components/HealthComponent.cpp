// Sajjad Mirshaby 2022


#include "Components/HealthComponent.h"

#include "TinyTankGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/TinyTank.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = DefaultHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* Instigator, AActor* DamageCauser)
{
	if(Damage <= 0 || IsDead) return;
	
	CurrentHealth -= Damage;
	
	if(ATinyTank* Player = Cast<ATinyTank>(GetOwner()))
	{
		// Update Progress Bar
		Player->OnHealthChanged.Broadcast(CurrentHealth);
	}
	
	if(CurrentHealth <= 0)
	{
		IsDead = true;
		
		// Play Explosion Sound
		UGameplayStatics::PlaySoundAtLocation(this,ExplosionSound,GetOwner()->GetActorLocation(),GetOwner()->GetActorRotation());

		// Spawn Explosion Particle
		UGameplayStatics::SpawnEmitterAtLocation(this,ExplosionEffect,GetOwner()->GetActorLocation());
		
		//Access to GameMode
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		ATinyTankGameMode* TinyTankGM = Cast<ATinyTankGameMode>(GameMode);
		
		if(ATinyTank* Player = Cast<ATinyTank>(GetOwner()))
		{
			GetWorld()->GetFirstPlayerController()->StartSpectatingOnly();
			TinyTankGM->LoadGameOverWidget();
		}
		else
		{
			TinyTankGM->EnemyDead();
		}
		
		// Destroy Tank or Turret
		GetOwner()->Destroy();
	}
}

