// Fill out your copyright notice in the Description page of Project Settings.


#include "Health/ProjektHealthComponent.h"

// Sets default values for this component's properties
UProjektHealthComponent::UProjektHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	DefaultHealth = 100;
	Health = DefaultHealth;
}


// Called when the game starts
void UProjektHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UProjektHealthComponent::TakeDamage);
	}
	
}

void UProjektHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	if (Health <= 0) {
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Orange, TEXT("hp"));
	}
}

