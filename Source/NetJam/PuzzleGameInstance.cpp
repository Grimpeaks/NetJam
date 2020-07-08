// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleGameInstance.h"
#include "Engine/Engine.h"


UPuzzleGameInstance::UPuzzleGameInstance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMainMenu> MainMenuBPClass(TEXT("/Game/Blueprint/BP_WidgetGameMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;

	ms_menuClass = MainMenuBPClass.Class;
}

void UPuzzleGameInstance::Host()
{
	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr)) return;

	engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting a server"));

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/PuzzleGame/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzleGameInstance::Join(const FString& ip)
{
	UEngine* engine = GetEngine();
	if (!ensure(engine != nullptr)) return;

	engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining a server : %s"), *ip));

	APlayerController* playerController = GetFirstLocalPlayerController();
	if (!ensure(playerController != nullptr)) return;

	playerController->ClientTravel(ip, ETravelType::TRAVEL_Absolute);
}

void UPuzzleGameInstance::LoadGameMenu()
{
	if (!ensure(ms_menuClass != nullptr)) return;
	auto menu = CreateWidget<UMainMenu>(this, ms_menuClass);
	menu->Setup();
}