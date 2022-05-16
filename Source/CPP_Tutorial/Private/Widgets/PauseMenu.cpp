// Sajjad Mirshaby 2022


#include "Widgets/PauseMenu.h"


#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UPauseMenu::Initialize()
{
	bool bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	
	// Our Code
	UE_LOG(LogTemp,Warning,TEXT("Pause Menu Initialize!"));
	
	return true;
}

void UPauseMenu::QuitTinyTank()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("Quit");
}

void UPauseMenu::ResumeGame()
{
	UGameplayStatics::SetGlobalTimeDilation(this,1);
	GetWorld()->GetFirstPlayerController()->EnableInput(GetWorld()->GetFirstPlayerController());
	

	RemoveFromParent();
}
