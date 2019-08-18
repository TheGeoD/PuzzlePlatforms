// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

/**
 * 
 */

class UTextBlock; 
class UMainMenu; 
class UButton; 
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

public: 
	void Setup(UMainMenu* Parent, struct FServerData ServerName, int32 Index);

	UPROPERTY(BlueprintReadOnly)
	bool Selected = false; 
protected: 
	virtual bool Initialize() override; 

	UFUNCTION()
	void UserClickedHere(); 
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConnectionFraction;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HostUser; 

	UPROPERTY(meta = (BindWidget))
	UButton* ServerSelectRowButton;
	
	int32 Index;

	UPROPERTY()
	UMainMenu* Parent; 
};
