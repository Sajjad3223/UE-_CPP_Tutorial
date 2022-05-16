// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player_HUD.generated.h"

/**
 * 
*/



UCLASS()
class CPP_TUTORIAL_API UPlayer_HUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayer_HUD(const FObjectInitializer& ObjectInitializer);
	
	virtual bool Initialize() override;
private:
	UFUNCTION()
	void OnPauseClicked();

	UFUNCTION()
	void HealthChanged(float Health);

	UFUNCTION()
	void EnemyDead(int CurrentEnemies ,int AllEnemies);
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* Health_Progress = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Enemies = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* Pause = nullptr;

	TSubclassOf<class UPauseMenu> PauseMenuClass;
};
