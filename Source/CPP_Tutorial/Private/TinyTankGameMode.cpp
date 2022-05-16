// Sajjad Mirshaby 2022


#include "TinyTankGameMode.h"

#include "Pawns/EnemyPawn.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#define OUT

ATinyTankGameMode::ATinyTankGameMode()
{
	ConstructorHelpers::FClassFinder<AEnemyPawn> Enemy_Class(TEXT("/Game/Turret/BP_TurretEnemy"));
	ConstructorHelpers::FClassFinder<UUserWidget> LoadingWidgetClass(TEXT("/Game/Widgets/WBP_Loading"));
	ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetClass(TEXT("/Game/Widgets/WBP_GameOver"));
	if(Enemy_Class.Class)
		EnemyClass = Enemy_Class.Class;
	if(LoadingWidgetClass.Class)
		LoadingClass = LoadingWidgetClass.Class;
	if(GameOverWidgetClass.Class)
		GameOverClass = GameOverWidgetClass.Class;
	
}

void ATinyTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this,EnemyClass,OUT Enemies);

	AllEnemiesCount = Enemies.Num();
	CurrentEnemiesCount = AllEnemiesCount;

	LoadingWidget = CreateWidget<UUserWidget>(GetWorld(),LoadingClass,FName("Loading Widget"));
	UGameplayStatics::GetPlayerPawn(this,0)->DisableInput(GetWorld()->GetFirstPlayerController());
	LoadingWidget->AddToViewport();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ATinyTankGameMode::RemoveLoadingWidget,3.f,false);
}

void ATinyTankGameMode::RemoveLoadingWidget()
{
	UGameplayStatics::GetPlayerPawn(this,0)->EnableInput(GetWorld()->GetFirstPlayerController());
	LoadingWidget->RemoveFromParent();
}

void ATinyTankGameMode::UpdateEnemies()
{
	OnEnemyDead.Broadcast(CurrentEnemiesCount,AllEnemiesCount);
}

void ATinyTankGameMode::EnemyDead()
{
	CurrentEnemiesCount--;

	if(CurrentEnemiesCount <= 0)
	{
		LoadGameOverWidget();
	}

	UpdateEnemies();
}

void ATinyTankGameMode::LoadGameOverWidget()
{
	UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(),GameOverClass,FName("GameOver Widget"));
	UGameplayStatics::GetPlayerPawn(this,0)->DisableInput(GetWorld()->GetFirstPlayerController());
	GameOverWidget->AddToViewport();
}
