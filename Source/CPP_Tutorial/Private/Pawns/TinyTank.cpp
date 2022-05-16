// Sajjad Mirshaby 2022


#include "Pawns/TinyTank.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"

// Sets default values
ATinyTank::ATinyTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->AttachToComponent(SpringArm,FAttachmentTransformRules::KeepRelativeTransform);

	PawnMovement=CreateDefaultSubobject<UFloatingPawnMovement>(FName("Movement"));	
}

// Called when the game starts or when spawned
void ATinyTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATinyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	FVector MouseLocation = HitResult.ImpactPoint;

	LookAtTarget(MouseLocation);
}

// Called to bind functionality to input
void ATinyTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ATinyTank::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ATinyTank::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight",this,&ATinyTank::TurnRight);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ATinyTank::Fire);
}

void ATinyTank::MoveForward(float Value)
{
	this->AddMovementInput(GetActorForwardVector(),Value);
}
void ATinyTank::MoveRight(float Value)
{
	BodyMesh->AddRelativeRotation(FRotator(0,Value * BodyRotationSpeed * GetWorld()->GetDeltaSeconds(),0));
}

void ATinyTank::TurnRight(float Value)
{
	BodyMesh->AddRelativeRotation(FRotator(0,Value * TurretRotationSpeed * GetWorld()->GetDeltaSeconds(),0));
}

