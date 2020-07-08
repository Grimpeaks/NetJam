// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MainMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NETJAM_API UPuzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& ip);

	UFUNCTION(BlueprintCallable)
	void LoadGameMenu();

	TSubclassOf<UMainMenu> ms_menuClass;
};
