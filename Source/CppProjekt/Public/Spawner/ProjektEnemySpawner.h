// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjektEnemySpawner.generated.h"

UCLASS()
class CPPPROJEKT_API AProjektEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjektEnemySpawner();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
		float SpawnRate;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<AActor> ActorToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();
	void SpawnTimer();

private:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	int32 bCanSpawn = 1;

	FTimerHandle TimerHandle_SpawnTimerExpired;
};
