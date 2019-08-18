// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "PlatformTrigger.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/GameOverlayMenu.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionInterface.h"
#include "UnrealNames.h"

const static FName SESSION_NAME = TEXT("Game");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("ServerName"); 


UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer &ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if(MenuBPClass.Class != NULL)
	{
		MenuClass = MenuBPClass.Class; 
	}
	ConstructorHelpers::FClassFinder<UUserWidget> OverlayBPClass(TEXT("/Game/MenuSystem/WBP_Overlay"));
	if (OverlayBPClass.Class != NULL)
	{
		OverlayClass = OverlayBPClass.Class;
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor called"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Online Subsystem found"));
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Declaring Delegate"));

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnJoinSessionComplete); 
			RequestRefresh(); 
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Delegate Declaration failed"));
		}
		UE_LOG(LogTemp, Warning, TEXT("Found %s"), *Subsystem->GetSubsystemName().ToString());
	}
}


void UPuzzlePlatformsGameInstance::Host(FString Name)
{
	CustomServerName = Name; 
	if (SessionInterface.IsValid())
	{

		auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
		if(ExistingSession)
		{
			UE_LOG(LogTemp, Warning, TEXT("Destroying Session before new session can be created. "));
			SessionInterface->DestroySession(NAME_GameSession);
		}
		else
		{
			CreateSession(); 
		}
	}
}

void UPuzzlePlatformsGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;

		if(IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			SessionSettings.bIsLANMatch = true;
		}
		else
		{
			SessionSettings.bIsLANMatch = false;
		}

		SessionSettings.Set(SERVER_NAME_SETTINGS_KEY, CustomServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionSettings.NumPublicConnections = 5;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true; 

		SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
	}
}

void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName SessionName, bool bSucceeded)
{
	if (bSucceeded)
	{
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, TEXT("Hosting"));
		UWorld* World = GetWorld();
		if (World)
		{
			if (Menu)
			{
				Menu->TearDown();
			}
			World->ServerTravel("/Game/Maps/Lobby?listen");
		}
	}
	else
	{
		return; 
	}
}

void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName SessionName, bool bSucceeded)
{
	if(bSucceeded && SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Destroyed... "));
		UE_LOG(LogTemp, Warning, TEXT("Creating new Session"));

		CreateSession();  
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Destruction failed"));
	}
}

void UPuzzlePlatformsGameInstance::OnFindSessionComplete(bool bSucceeded)
{
	if(!bSucceeded || !SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Error in finding Session"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Find Session Completed"));
		FString Server;
		TArray<FServerData> SessionArray; 
		for(const FOnlineSessionSearchResult& Sessions : SessionSearch->SearchResults)
		{
			FServerData Data; 
			if(!Sessions.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("null session found"));
			}
			else
			{
				if(Sessions.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, Server))
				{
					Data.Name = Server; 
				}
				else
				{
					Data.Name = Sessions.Session.GetSessionIdStr(); 
				}
				Data.MaxPlayers = Sessions.Session.SessionSettings.NumPublicConnections;
				Data.CurrentPlayers = (Sessions.Session.SessionSettings.NumPublicConnections - 
					Sessions.Session.NumOpenPublicConnections);
				Data.OwnerName = Sessions.Session.OwningUserName;
				SessionArray.Add(Data);
			}
			
		}
		if (Menu)
		{
				Menu->SetServerList(SessionArray);
		}
	}
}


void UPuzzlePlatformsGameInstance::Join(uint32 Index)
{
	if(!SessionInterface.IsValid() || !SessionSearch.IsValid())
	{
		return; 
	}
	if (Menu)
	{
		Menu->TearDown();
	}
	SessionInterface->JoinSession(0, NAME_GameSession, SessionSearch->SearchResults[Index]);

}

void UPuzzlePlatformsGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}
	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect String"));
		return;
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}
	APlayerController* PlayerController = GetFirstLocalPlayerController(); 
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this, MenuClass);
		if (Menu)
		{
			Menu->Setup();
			Menu->SetMenuInterface(this); 
		}
	}
}

void UPuzzlePlatformsGameInstance::ShowOverlay()
{
	if (OverlayClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Show Overlay"));

		UMenuWidget* OverlayMenu = CreateWidget<UMenuWidget>(this, OverlayClass);
		if (OverlayMenu)
		{
			OverlayMenu->Setup(); 
			OverlayMenu->SetMenuInterface(this); 
		}
	}
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController(); 
	
	if (PlayerController)
	{
		PlayerController->ClientTravel("/Game/Maps/Menu", ETravelType::TRAVEL_Absolute);

	}
}

void UPuzzlePlatformsGameInstance::RequestRefresh()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 100; 
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals); 
		SessionSearch->bIsLanQuery = false;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPuzzlePlatformsGameInstance::StartSession()
{
	if(SessionInterface.IsValid())
	{
		SessionInterface->StartSession(NAME_GameSession); 
	}
}

