// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class NETJAM_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

	FVector m_basePosition;
	FVector m_startingPosition;
	FVector m_endingPosition;

	bool m_canMove = false;
	int m_nbCanMove = 0;

public:
	AMovingPlatform();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void setCanMove(bool can);

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (DisplayName = "Speed in cm/s"))
	float Speed = 250;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (DisplayName = "Target"), meta = (MakeEditWidget = true))
	FVector TargetLocation;
};
