// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "../CPP_TutorialGameModeBase.h"
#include "TinyTankGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyDead,int,CurrentEnemies,int,AllEnemies);

UCLASS()
class CPP_TUTORIAL_API ATinyTankGameMode : public ACPP_TutorialGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	ATinyTankGameMode();

	//Begin Play
	virtual void BeginPlay() override;

	void UpdateEnemies();

	//Enemy Dead
	void EnemyDead();
	//Enemy Dead
	void LoadGameOverWidget();

	//Disable Loading
	void RemoveLoadingWidget();

	FEnemyDead OnEnemyDead;
	
private:
	//Enemy Class
	TSubclassOf<class AEnemyPawn> EnemyClass;

	//All Enemies Count
	int AllEnemiesCount;

	// Current Enemies Count
	int CurrentEnemiesCount;

	TSubclassOf<class UUserWidget> GameOverClass;
	TSubclassOf<class UUserWidget> LoadingClass;
	UUserWidget* LoadingWidget = nullptr;
};
