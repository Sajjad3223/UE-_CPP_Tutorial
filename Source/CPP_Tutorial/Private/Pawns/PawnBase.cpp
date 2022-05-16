// Sajjad Mirshaby 2022


#include "Pawns/PawnBase.h"

#include "Actors/Projectile.h"
#include "Components/HealthComponent.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BodyMesh"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("BarrelMesh"));
	BarrelMesh->SetupAttachment(TurretMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(BarrelMesh);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("HealthComponent"));
}

// Called when the game starts or when spawned
void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APawnBase::LookAtTarget(FVector TargetLocation)
{
	FVector TurretLocation = TurretMesh->GetComponentLocation();
	FVector TargetFixedLocation = FVector(TargetLocation.X,TargetLocation.Y,TurretLocation.Z);
	FRotator NewTurretRotation = FVector(TargetFixedLocation - TurretLocation).Rotation();

	FRotator SmoothRotation = FMath::Lerp(TurretMesh->GetComponentRotation(),NewTurretRotation,TurretRotationSpeed  * GetWorld()->GetDeltaSeconds());

	TurretMesh->SetWorldRotation(SmoothRotation);
}

void APawnBase::Fire()
{
	// Spawn Projectile In Location
	AProjectile* TempProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentTransform());
	TempProjectile->SetOwner(this);
}