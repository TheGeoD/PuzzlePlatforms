// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGameMode.h"
#include "PuzzlePlatformsGameInstance.h"


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer); 
	++PlayerCount; 
	if(PlayerCount == StartPlayerCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max Players have been rached... Traveling")); 
		GetWorldTimerManager().SetTimer(StartGameHandle, this, &ALobbyGameMode::StartGameOnTimer, 10.0f, false);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting); 
	--PlayerCount; 
}

void ALobbyGameMode::StartGameOnTimer()
{
	UPuzzlePlatformsGameInstance* GameInstance = Cast<UPuzzlePlatformsGameInstance>(GetGameInstance()); 
	if (GameInstance)
	{
		GameInstance->StartSession(); 
		UWorld* World = GetWorld();
		if (World)
		{
			bUseSeamlessTravel = true;
			World->ServerTravel("/Game/Maps/ThirdPersonExampleMap?listen");
		}
	}
	
}
