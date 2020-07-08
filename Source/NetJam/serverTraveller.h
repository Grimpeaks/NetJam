// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "serverTraveller.generated.h"

UCLASS()
class NETJAM_API AserverTraveller : public AActor
{
	GENERATED_BODY()
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Sets default values for this actor's properties
	AserverTraveller();

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	UBoxComponent* m_collider;

	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* m_mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int nbPlayers;

};
