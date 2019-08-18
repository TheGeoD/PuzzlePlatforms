// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ScrollBox.h"
#include "MenuSystem/ServerRow.h"


UMainMenu::UMainMenu(const FObjectInitializer &ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> ServerRowBPClass(TEXT("/Game/MenuSystem/WBP_ServerRow"));
	if (ServerRowBPClass.Class != NULL)
	{
		ServerRowClass = ServerRowBPClass.Class;
	}
}

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if(!Success)
	{
		return false;
	}
	if(HostButton)
	{ 
		HostButton->OnClicked.AddDynamic(this, &UMainMenu::UserClickedHost);
	} 
	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UMainMenu::UserClickedJoin);
	}
	if(CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &UMainMenu::UserClickedCancel); 
	}
	if (JoinAtIpButton)
	{
		JoinAtIpButton->OnClicked.AddDynamic(this, &UMainMenu::UserClickedJoinAtIp);
	}
	if(ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UMainMenu::ExitGame);
	}
	if (RefreshButton)
	{
		RefreshButton->OnClicked.AddDynamic(this, &UMainMenu::RefreshServerList);
	}
	if (ReturnToMainButton)
	{
		ReturnToMainButton->OnClicked.AddDynamic(this, &UMainMenu::UserClickedCancel);
	}
	if (LaunchServerButton)
	{
		LaunchServerButton->OnClicked.AddDynamic(this, &UMainMenu::LaunchServer);
	}
	return true; 
}


void UMainMenu::UserClickedHost()
{

	if (MenuSwitcher)
	{
		if (HostMenu)
		{
			MenuSwitcher->SetActiveWidget(HostMenu);
		}
	}

}

void UMainMenu::UserClickedJoin()
{
	if (MenuSwitcher)
	{
		if (JoinMenu)
		{
			MenuSwitcher->SetActiveWidget(JoinMenu);
		}
	}
}

void UMainMenu::UserClickedCancel()
{
	if (MenuSwitcher)
	{
		if (MainMenu)
		{
			MenuSwitcher->SetActiveWidget(MainMenu);
		}
	}
}

void UMainMenu::UserClickedJoinAtIp()
{
	if (SelectedIndex.IsSet() && MenuInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index, %d"), SelectedIndex.GetValue());
		MenuInterface->Join(SelectedIndex.GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected index not set"));
	}
}

void UMainMenu::ExitGame()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(MenuInterface);
	if(GameInstance)
	{
		UGameViewportClient* Viewport = GameInstance->GetGameViewportClient();
		if(Viewport)
		{
			Viewport->ConsoleCommand("quit"); 
		}
	}
}

void UMainMenu::RefreshServerList()
{
	if(MenuInterface)
	{
		MenuInterface->RequestRefresh(); 
	}
}

void UMainMenu::LaunchServer()
{
	FString UserEnteredServerName = CustomServerName->GetText().ToString();
	if(MenuInterface)
	{
		MenuInterface->Host(UserEnteredServerName);
	}
}

void UMainMenu::UpdateChildren()
{
	int32 x = ServerList->GetChildrenCount(); 
	for(int32 i = 0; i < x ; i++)
	{
		UServerRow* UpdatedRow = Cast<UServerRow>(ServerList->GetChildAt(i));
		if(UpdatedRow)
		{
			if(SelectedIndex.IsSet())
			{
				UpdatedRow->Selected = (SelectedIndex.GetValue() == i); 
			}
		}
	}
}

void UMainMenu::SetServerList(TArray<FServerData> Servernames)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return; 
	}

	ServerList->ClearChildren(); 
	uint32 i = 0; 
	for (const FServerData ServerName : Servernames)
	{
		Row = CreateWidget<UServerRow>(this, ServerRowClass); 
		if(Row)
		{
			Row->Setup(this, ServerName, i); 

			ServerList->AddChild(Row); 
		}
		++i; 
	}
}

void UMainMenu::SelectIndex(uint32 Index)
{
	SelectedIndex = Index;
	UpdateChildren(); 
}
