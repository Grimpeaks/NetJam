// Fill out your copyright notice in the Description page of Project Settings.


#include "FeedbackObj.h"

// Sets default values
AFeedbackObj::AFeedbackObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("feedbackObjMesh"));
	m_bigCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("feedbackObjBigCollider"));
	m_smallCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("feedbackObjSmallCollider"));
	RootComponent = m_mesh;
	m_bigCollider->SetupAttachment(m_mesh);
	m_smallCollider->SetupAttachment(m_mesh);
}

// Called when the game starts or when spawned
void AFeedbackObj::BeginPlay()
{
	Super::BeginPlay();
	m_bigCollider->OnComponentBeginOverlap.AddDynamic(this, &AFeedbackObj::OnOverlapBeginFeedback);
	m_bigCollider->OnComponentEndOverlap.AddDynamic(this, &AFeedbackObj::OnOverlapEndFeedback);

	m_smallCollider->OnComponentBeginOverlap.AddDynamic(this, &AFeedbackObj::OnOverlapBeginInteract);
	m_smallCollider->OnComponentEndOverlap.AddDynamic(this, &AFeedbackObj::OnOverlapEndInteract);
}

// Called every frame
void AFeedbackObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFeedbackObj::feedbackStart()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("feedbackStart"));
		multicast_FeedbackStart_Implementation();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("RPC feedbackStart()"));
	server_FeedbackStart_Implementation();
}

void AFeedbackObj::feedbackStop()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("feedbackStop"));
		multicast_FeedbackStop_Implementation();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("RPC feedbackStop()"));
	server_FeedbackStop_Implementation();
}

void AFeedbackObj::interactStart()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("interactStart"));

		UWorld* world = GetWorld();
		if (!ensure(world != nullptr)) return;
		world->ServerTravel("/Game/PuzzleGame/Maps/ThirdPersonLvl1?listen");

		multicast_InteractStart();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("RPC interactStart()"));
	server_InteractStart_Implementation();
}

void AFeedbackObj::interactStop()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("interactStop"));
		multicast_InteractStop();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("RPC interactStop()"));
	server_InteractStop_Implementation();
}

void AFeedbackObj::server_FeedbackStart_Implementation()
{
	multicast_FeedbackStart_Implementation();
}

void AFeedbackObj::server_FeedbackStop_Implementation()
{
	multicast_FeedbackStop_Implementation();
}

void AFeedbackObj::server_InteractStart_Implementation()
{
	multicast_InteractStart_Implementation();
}
void AFeedbackObj::server_InteractStop_Implementation()
{
	multicast_InteractStop_Implementation();
}

void AFeedbackObj::multicast_FeedbackStart_Implementation()
{
	FeedbackStartBP();
}

void AFeedbackObj::multicast_FeedbackStop_Implementation()
{
	FeedbackStopBP();
}

void AFeedbackObj::multicast_InteractStart_Implementation()
{
	InteractStartBP();
}

void AFeedbackObj::multicast_InteractStop_Implementation()
{
	InteractStopBP();
}

void AFeedbackObj::OnOverlapBeginFeedback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBeginFeedback"));
	feedbackStart();
}

void AFeedbackObj::OnOverlapEndFeedback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEndFeedback"));
	feedbackStop();
}

void AFeedbackObj::OnOverlapBeginInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBeginInteract"));
	interactStart();
}

void AFeedbackObj::OnOverlapEndInteract(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEndInteract"));
	interactStop();
}



