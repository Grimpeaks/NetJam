// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

void UMainMenu::join()
{
	UE_LOG(LogTemp, Warning, TEXT("Join Action"));
	auto world = GetWorld();
	auto player = world->GetFirstPlayerController();

	if (!ensure(world != nullptr)) return;
	if (!ensure(player != nullptr)) return;

	FInputModeGameOnly inputMode;

	player->SetInputMode(inputMode);
	player->bShowMouseCursor = false;
	player->ConsoleCommand("Join " + m_IP);
}

void UMainMenu::host()
{
	UE_LOG(LogTemp, Warning, TEXT("Host Action"));
	auto world = GetWorld();
	auto player = world->GetFirstPlayerController();

	if (!ensure(world != nullptr)) return;
	if (!ensure(player != nullptr)) return;

	FInputModeGameOnly inputMode;

	player->SetInputMode(inputMode);
	player->bShowMouseCursor = false;
	player->ConsoleCommand("Host");
}

bool UMainMenu::Initialize()
{
	bool isInit;
	isInit = Super::Initialize();

	if (!isInit) { return false; }

	if (!ensure(btnJoin != nullptr) || !ensure(btnHost != nullptr)) { return false; }

	btnJoin->OnClicked.AddDynamic(this, &UMainMenu::join);
	btnHost->OnClicked.AddDynamic(this, &UMainMenu::host);

	return true;
}

void UMainMenu::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	auto world = GetWorld();
	auto player = world->GetFirstPlayerController();

	if (!ensure(world != nullptr)) return;
	if (!ensure(player != nullptr)) return;

	FInputModeUIOnly inputMode;

	inputMode.SetWidgetToFocus(TakeWidget());
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	player->SetInputMode(inputMode);
	player->bShowMouseCursor = true;
}

void UMainMenu::setIPText(FString newIP)
{
	m_IP = newIP;
	UE_LOG(LogTemp, Warning, TEXT("IP modified : %s"), *m_IP);
}


