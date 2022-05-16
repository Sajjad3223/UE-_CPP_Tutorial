// Sajjad Mirshaby 2022


#include "Pawns/EnemyPawn.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(this,0);
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector PlayerLocation = PlayerPawn->GetActorLocation();
	if(FVector::Dist(GetActorLocation(),PlayerLocation) <= MaxDistance)
	{
		LookAtTarget(PlayerLocation);
		if(FireTimer >= FireRate)
		{
			Fire();
			FireTimer = 0;
		}
	}
	FireTimer += DeltaTime;
}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

