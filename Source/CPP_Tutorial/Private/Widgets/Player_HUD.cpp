// Sajjad Mirshaby 2022


#include "Widgets/Player_HUD.h"

#include "TinyTankGameMode.h"
#include "Pawns/TinyTank.h"
#include "Widgets/PauseMenu.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

#include "UObject/ConstructorHelpers.h"

#define LOCTEXT_NAMESPACE "UpdateText"

UPlayer_HUD::UPlayer_HUD(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	// Get Pause menu Class Reference
	ConstructorHelpers::FClassFinder<UPauseMenu> PauseMenuReference(TEXT("/Game/Widgets/WBP_PauseMenu"));
	if(!PauseMenuReference.Class)
	{
		UE_LOG(LogTemp,Error,TEXT("Could not Find Pause menu Reference!!!"))
		return;
	}
	else
		UE_LOG(LogTemp,Warning,TEXT("Pause menu Reference Found!"))

	//Fill Pause menu Class Variable
	PauseMenuClass = PauseMenuReference.Class;
}

bool UPlayer_HUD::Initialize()
{
	bool bSuccess = Super::Initialize();
	if(!bSuccess) return false;
	
	// Our Code
	Pause->OnClicked.AddDynamic(this,&UPlayer_HUD::OnPauseClicked);

	if(ATinyTank* PlayerPawn = Cast<ATinyTank>(UGameplayStatics::GetPlayerPawn(this,0)))
	{
		PlayerPawn->OnHealthChanged.AddDynamic(this,&UPlayer_HUD::HealthChanged);
	}

	//Access to GameMode
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
	ATinyTankGameMode* TinyTankGM = Cast<ATinyTankGameMode>(GameMode);
	
	//Bind Function to event
	TinyTankGM->OnEnemyDead.AddDynamic(this,&UPlayer_HUD::EnemyDead);

	TinyTankGM->UpdateEnemies();
	
	return true;
}

void UPlayer_HUD::OnPauseClicked()
{
	// TODO Show Pause Menu
	if(!PauseMenuClass) return;
	UPauseMenu* CreatedPauseMenu = CreateWidget<UPauseMenu>(GetWorld(),PauseMenuClass,FName("Pause Menu Widget"));

	UGameplayStatics::SetGlobalTimeDilation(this,0);
	GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());
	
	CreatedPauseMenu->AddToViewport();
}

void UPlayer_HUD::HealthChanged(float Health)
{
	float CurrentHealthInPercent = Health / 100; 
	Health_Progress->SetPercent(CurrentHealthInPercent);
}

void UPlayer_HUD::EnemyDead(int CurrentEnemies, int AllEnemies)
{
	FText EnemiesText = FText::Format(LOCTEXT("UpdateText","{0} / {1}"),AllEnemies,CurrentEnemies);
	Enemies->SetText(EnemiesText);
}
