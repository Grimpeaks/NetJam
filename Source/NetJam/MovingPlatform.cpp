// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	//On dit que l'objet peut être update
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	m_basePosition = GetActorLocation();
	m_startingPosition = GetActorLocation();
	m_endingPosition = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HasAuthority())
	{
		if (m_canMove)
		{
			auto currentLocation = GetActorLocation();
			float distanceTravelled = (currentLocation - m_startingPosition).Size();
			float m_totalDistance = (m_startingPosition - m_endingPosition).Size();

			if (distanceTravelled >= m_totalDistance)
			{
				auto temp = m_endingPosition;
				m_endingPosition = m_startingPosition;
				m_startingPosition = temp;
			}

			auto direction = (m_endingPosition - m_startingPosition).GetSafeNormal();
			currentLocation += FVector(Speed * DeltaSeconds * direction);
			SetActorLocation(currentLocation);
		}
		else
		{
			auto currentLocation = GetActorLocation();
			float distanceTravelled = (currentLocation - m_startingPosition).Size();
			float m_totalDistance = (m_startingPosition - m_endingPosition).Size();

			if (distanceTravelled < m_totalDistance)
			{
				if (m_endingPosition != m_basePosition)
				{
					auto temp = m_endingPosition;
					m_endingPosition = m_startingPosition;
					m_startingPosition = temp;
				}
				auto direction = (m_endingPosition - m_startingPosition).GetSafeNormal();
				currentLocation += FVector(Speed * 2 * DeltaSeconds * direction);
				SetActorLocation(currentLocation);
			}
		}
	}
}

void AMovingPlatform::setCanMove(bool can)
{
	m_canMove = can;
}
