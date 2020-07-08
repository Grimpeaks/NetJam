// Fill out your copyright notice in the Description page of Project Settings.


#include "DallePression.h"

// Sets default values
ADallePression::ADallePression()
{
	//Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("dallePressionMesh"));
	m_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("dallePressionCollider"));
	RootComponent = m_mesh;
	m_collider->SetupAttachment(m_mesh);

}

// Called when the game starts or when spawned
void ADallePression::BeginPlay()
{
	Super::BeginPlay();
	m_collider->OnComponentBeginOverlap.AddDynamic(this, &ADallePression::OnOverlapBegin);
	m_collider->OnComponentEndOverlap.AddDynamic(this, &ADallePression::OnOverlapEnd);
}

// Called every frame
void ADallePression::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool mustMove = false;

	if (HasAuthority())
	{
		for (ANetJamCharacter* actorPtr : overlapActors)
		{
			if (actorPtr->getMouseDown())
			{
				mustMove = true;
				break;
			}
		}

		for (AMovingPlatform* platformPtr : m_movingPlatforms)
		{
			platformPtr->setCanMove(mustMove);
		}
	}
}

void ADallePression::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	overlapActors.Add(reinterpret_cast<ANetJamCharacter*>(OtherActor));
}

void ADallePression::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	overlapActors.Remove(reinterpret_cast<ANetJamCharacter*>(OtherActor));
}

