// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Weapons/ProjektWeapon_1.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Interact/InteractInterface.h"


// Sets default values
AProjektWeapon_1::AProjektWeapon_1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	MeshComp->SetupAttachment(RootComponent);
	//MeshComp->OnComponentHit.AddDynamic(this, &AProjektWeapon_1::OnHit);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	MovementComp->UpdatedComponent = MeshComp;
	MovementComp->InitialSpeed = 3000.f;
	MovementComp->MaxSpeed = 3000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bShouldBounce = false;
	MovementComp->ProjectileGravityScale = 0.f; // No gravity

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjektWeapon_1::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this, &AProjektWeapon_1::OnHit);
}

void AProjektWeapon_1::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor);
	if ((OtherActor != nullptr) && (OtherComp != nullptr))
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("onHit")));
		if (Interface)
		{
			Interface->Execute_OnInteract(OtherActor, this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("onOverlapBegin")));
		}
		Destroy();
	}
}

void AProjektWeapon_1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor);
	if (Interface)
	{
		//Interface->Execute_OnInteract(OtherActor, this);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("onOverlapBegin")));
	}
}

