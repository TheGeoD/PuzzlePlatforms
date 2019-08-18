// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "MainMenu.generated.h"

/**
 * 
 */
class UButton;
class UWidgetSwitcher;
class UEditableTextBox;
class UScrollBox; 
class UPanelWidget;
class UServerRow; 

USTRUCT()
struct FServerData
{
	GENERATED_BODY()
	
	FString Name; 
	uint16 CurrentPlayers; 
	uint16 MaxPlayers; 
	uint32 Ping; 
	FString OwnerName; 

};

UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
public: 
	UMainMenu(const FObjectInitializer &ObjectInitializer);

	void SetServerList(TArray<FServerData> Servernames);
	
	void SelectIndex(uint32 Index); 
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void UserClickedHost();
	
	UFUNCTION()
	void UserClickedJoin();

	UFUNCTION()
	void UserClickedCancel();

	UFUNCTION()
	void UserClickedJoinAtIp();
	
	UFUNCTION()
	void ExitGame();

	UFUNCTION()
	void RefreshServerList(); 

	UFUNCTION()
	void LaunchServer(); 

private: 

	void UpdateChildren(); 

	UPROPERTY(meta = (BindWidget))
	UButton* HostButton; 

	TSubclassOf<UUserWidget> ServerRowClass;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ReturnToMainButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinAtIpButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LaunchServerButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CustomServerName;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* ServerList; 

	UPROPERTY()
	UServerRow* Row; 

	TOptional<uint32> SelectedIndex;

	FString SessionName; 
};
