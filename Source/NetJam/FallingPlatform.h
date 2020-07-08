// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "FallingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class NETJAM_API AFallingPlatform : public AActor
{
	GENERATED_BODY()
	
	FVector m_basePosition;
	FRotator m_baseRotation;
	int nbOn;
	float timeOn;

public:
	AFallingPlatform();

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	UBoxComponent* m_collider;

	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* m_mesh;

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (DisplayName = "Standing time in s"))
	float standingTime = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Gameplay", meta = (DisplayName = "Reset time in s"))
	float resetTime = 5.0f;

	FTimerHandle standingTimerHandle;
	FTimerHandle resetTimerHandle;

private:
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void disableGravity();

	void resetPos();
};
