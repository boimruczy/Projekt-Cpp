// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy1.generated.h"

UCLASS()
class SPACE_API AEnemy1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	float Hp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
