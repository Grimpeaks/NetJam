// Fill out your copyright notice in the Description page of Project Settings.


#include "serverTraveller.h"

// Sets default values
AserverTraveller::AserverTraveller()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("travellerMesh"));
	m_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("travellerCollider"));
	RootComponent = m_mesh;
	m_collider->SetupAttachment(m_mesh);

}

// Called when the game starts or when spawned
void AserverTraveller::BeginPlay()
{
	Super::BeginPlay();
	m_collider->OnComponentBeginOverlap.AddDynamic(this, &AserverTraveller::OnOverlapBegin);
	nbPlayers = 0;
}

// Called every frame
void AserverTraveller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AserverTraveller::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	if (HasAuthority())
	world->ServerTravel("/Game/PuzzleGame/Maps/ThirdPersonLvl1?listen");
}