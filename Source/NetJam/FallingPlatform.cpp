// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPlatform.h"

AFallingPlatform::AFallingPlatform()
{
	//On dit que l'objet peut être update
	PrimaryActorTick.bCanEverTick = true;
	//SetMobility(EComponentMobility::Movable);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("fallingPlatformMesh"));
	m_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("fallingPlatformCollider"));
	RootComponent = m_mesh;
	m_collider->SetupAttachment(m_mesh);
	m_mesh->SetSimulatePhysics(false);
}

void AFallingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
		m_collider->OnComponentBeginOverlap.AddDynamic(this, &AFallingPlatform::OnOverlapBegin);
		m_collider->OnComponentEndOverlap.AddDynamic(this, &AFallingPlatform::OnOverlapEnd);
	}

	m_basePosition = GetActorLocation();
	m_baseRotation = GetActorRotation();
}

// Called every frame
void AFallingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFallingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		
		if (nbOn <= 0) { GetWorldTimerManager().SetTimer(standingTimerHandle, this, &AFallingPlatform::disableGravity, standingTime, false); }
		nbOn++;
	}
}

void AFallingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority())
	{
		nbOn--;
		if (nbOn <= 0)
		{
			GetWorldTimerManager().ClearTimer(standingTimerHandle);
		}
	}
}

void AFallingPlatform::disableGravity()
{
	m_mesh->SetSimulatePhysics(true);
	m_mesh->SetEnableGravity(true);
	GetWorldTimerManager().SetTimer(resetTimerHandle, this, &AFallingPlatform::resetPos, resetTime, true);
}

void AFallingPlatform::resetPos()
{
	if (nbOn <= 0)
	{
		m_mesh->SetSimulatePhysics(false);
		m_mesh->SetEnableGravity(false);
		SetActorLocation(m_basePosition);
		SetActorRotation(m_baseRotation);
		GetWorldTimerManager().ClearTimer(resetTimerHandle);
	}
}

