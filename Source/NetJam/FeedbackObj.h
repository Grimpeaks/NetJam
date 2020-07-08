// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "FeedbackObj.generated.h"

UCLASS()
class NETJAM_API AFeedbackObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFeedbackObj();

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	UBoxComponent* m_bigCollider;

	UPROPERTY(VisibleAnywhere, Category = "Collider")
	UBoxComponent* m_smallCollider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* m_mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void feedbackStart();
	UFUNCTION()
	void feedbackStop();
	UFUNCTION()
	void interactStart();
	UFUNCTION()
	void interactStop();

	UFUNCTION(Server, Reliable)
	void server_FeedbackStart();
	UFUNCTION(Server, Reliable)
	void server_FeedbackStop();
	UFUNCTION(Server, Reliable)
	void server_InteractStart();
	UFUNCTION(Server, Reliable)
	void server_InteractStop();

	UFUNCTION(NetMulticast, Reliable)
	void multicast_FeedbackStart();
	UFUNCTION(NetMulticast, Reliable)
	void multicast_FeedbackStop();
	UFUNCTION(NetMulticast, Reliable)
	void multicast_InteractStart();
	UFUNCTION(NetMulticast, Reliable)
	void multicast_InteractStop();

	UFUNCTION(BlueprintImplementableEvent)
	void FeedbackStartBP();
	UFUNCTION(BlueprintImplementableEvent)
	void FeedbackStopBP();
	UFUNCTION(BlueprintImplementableEvent)
	void InteractStartBP();
	UFUNCTION(BlueprintImplementableEvent)
	void InteractStopBP();

private:
	UFUNCTION()
	void OnOverlapBeginFeedback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndFeedback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnOverlapBeginInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEndInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
