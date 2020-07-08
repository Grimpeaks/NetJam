// Fill out your copyright notice in the Description page of Project Settings.
#include "MovingPlatform.h"
#include "NetJamCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "DallePression.generated.h"

UCLASS()
class NETJAM_API ADallePression : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADallePression();

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	UBoxComponent* m_collider;

	UPROPERTY(VisibleAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere, Category = "Moving platforms")
	TArray<AMovingPlatform*> m_movingPlatforms;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<ANetJamCharacter*> overlapActors;
};
