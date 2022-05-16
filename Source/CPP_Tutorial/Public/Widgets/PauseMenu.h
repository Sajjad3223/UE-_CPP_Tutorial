// Sajjad Mirshaby 2022

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class CPP_TUTORIAL_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
	
private:
	UFUNCTION(BlueprintCallable)
	void QuitTinyTank();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();
	
	UPROPERTY(meta=(BindWidget))
	class UButton* ResumeButton = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* OptionButton = nullptr;
	
	UPROPERTY(meta=(BindWidget))
	class UButton* QuitButton = nullptr;
	
	
};
