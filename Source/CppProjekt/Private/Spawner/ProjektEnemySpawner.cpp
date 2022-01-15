// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/ProjektEnemySpawner.h"

// Sets default values
AProjektEnemySpawner::AProjektEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 1.0f;
}

// Called when the game starts or when spawned
void AProjektEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AProjektEnemySpawner::SpawnEnemy, SpawnRate, false);
}

// Called every frame
void AProjektEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AProjektEnemySpawner::SpawnEnemy, SpawnRate);
	//AProjektEnemySpawner::SpawnEnemy();
}

void AProjektEnemySpawner::SpawnEnemy()
{
	FVector SpawnOffset = FVector(0, FMath::RandRange(-10.0f, 10.0f), 0);
	const FVector SpawnLocation = GetActorLocation() + SpawnOffset;
	const FVector FireDirection(1.0f, 0.0f, 0.0f);
	const FRotator FireRotation = FireDirection.Rotation();

	UWorld* const World = GetWorld();
	/*if (World != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActorRed = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FireRotation);

		//bCanSpawn = false;
		//World->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AProjektEnemySpawner::SpawnTimer, SpawnRate);
		
	}*/
	FActorSpawnParameters SpawnParams;
	AActor* SpawnedActorRed = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FireRotation);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AProjektEnemySpawner::SpawnEnemy, SpawnRate, false);
}

void AProjektEnemySpawner::SpawnTimer()
{
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_SpawnTimerExpired, this, &AProjektEnemySpawner::SpawnTimer, SpawnRate, false);
}

