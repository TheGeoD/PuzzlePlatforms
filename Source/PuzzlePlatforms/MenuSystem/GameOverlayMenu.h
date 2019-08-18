// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "GameOverlayMenu.generated.h"

/**
 * 
 */
class UButton;
class UOverlayMenuInterface; 
UCLASS()
class PUZZLEPLATFORMS_API UGameOverlayMenu : public UMenuWidget 
{
	GENERATED_BODY()
public: 
	virtual bool Initialize() override; 
protected:
	UFUNCTION()
	void UserClickedMainMenuButton();
	UFUNCTION()
	void UserClickedCancelButton(); 
private: 
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
};
