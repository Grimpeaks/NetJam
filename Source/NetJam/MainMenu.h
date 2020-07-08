// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"


/**
 * 
 */
UCLASS()
class NETJAM_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* btnJoin;
	UPROPERTY(meta = (BindWidget))
	UButton* btnHost;

	UFUNCTION()
	void join();

	UFUNCTION()
	void host();

	FString m_IP = "127.0.0.1";
	
protected :
	bool Initialize() override;

public :
	void Setup();

	UFUNCTION(BlueprintCallable)
	void setIPText(FString newIP);
};
