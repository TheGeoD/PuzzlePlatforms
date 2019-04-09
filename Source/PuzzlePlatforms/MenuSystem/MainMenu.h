// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 * 
 */

class UButton; 
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void UserClickedHost();
	
	UFUNCTION()
	void UserClickedJoin();
private: 

	UPROPERTY(meta = (BindWidget))
	UButton* Host; 

	UPROPERTY(meta = (BindWidget))
	UButton* Join;

	IMenuInterface* MenuInterface; 
};
