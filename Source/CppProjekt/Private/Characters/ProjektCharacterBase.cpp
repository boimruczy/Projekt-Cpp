// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ProjektCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Interact/InteractInterface.h"
#include "DrawDebugHelpers.h"
#include "Weapons/ProjektWeapon_1.h"


// Sets default values
AProjektCharacterBase::AProjektCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	MeshComp->SetupAttachment(RootComponent);

	TraceDistance = 2000.0f;

	MoveSpeed = 1.0f;

	GunOffset = FVector(90.0f, 0.0f, 0.0f);
	FireRate = 1.0f;
	bCanFire = true;
}

// Called when the game starts or when spawned
void AProjektCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AProjektCharacterBase::OnOverlapBegin);
}

void AProjektCharacterBase::MoveForward(float Value)
{
	if (Value) 
	{
		Value = Value * MoveSpeed;
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AProjektCharacterBase::MoveRight(float Value)
{
	if (Value)
	{
		Value = Value * MoveSpeed;
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AProjektCharacterBase::FireShoot()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Shoot"));
	const FVector SpawnLocation = GetActorLocation() + GunOffset;
	const FVector FireDirection (1.0f, 0.0f, 0.0f);
	const FRotator FireRotation = FireDirection.Rotation();

	//FActorSpawnParameters SpawnParams;
	//AActor* SpawnedActorRed = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FireRotation);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActorRed = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, FireRotation);
	}
	bCanFire = false;
	World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AProjektCharacterBase::ShootTimer, FireRate);
}

void AProjektCharacterBase::ShootTimer()
{
	bCanFire = true;
}

//test
void AProjektCharacterBase::InteractPressed()
{
	TraceForward();
	if (FocusedActor)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface)
		{
			Interface->Execute_OnInteract(FocusedActor, this);
		}
	}
}

void AProjektCharacterBase::TraceForward_Implementation()
{
	FVector Loc;
	FRotator Rot;
	FHitResult Hit;

	GetController()->GetPlayerViewPoint(Loc, Rot);

	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);

	FCollisionQueryParams TraceParams;

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);

	

	if (bHit)
	{
		//DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5, 5, 5), FColor::Emerald, false, 2.0f);

		AActor* Interactable = Hit.GetActor();

		if (Interactable) 
		{
			if (Interactable != FocusedActor)
			{
				if (FocusedActor)
				{
					IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
					if (Interface)
					{
						Interface->Execute_EndFocus(FocusedActor);
					}
				}
				IInteractInterface* Interface = Cast<IInteractInterface>(Interactable);
				if (Interface)
				{
					Interface->Execute_StartFocus(Interactable);
				}
				FocusedActor = Interactable;
			}
		}
		else
		{
			if (FocusedActor)
			{
				IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
				if (Interface)
				{
					Interface->Execute_EndFocus(FocusedActor);
				}
			}
			FocusedActor = nullptr;
		}
	}

}

void AProjektCharacterBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractInterface* Interface = Cast<IInteractInterface>(OtherActor);
	if (Interface)
	{
		Interface->Execute_OnInteract(OtherActor, this);
	}
}

void AProjektCharacterBase::Tick(float DeltaTime)
{
	TraceForward();
}

// Called to bind functionality to input
void AProjektCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AProjektCharacterBase::FireShoot);
	//PlayerInputComponent->BindAction("Shoot", IE_Released, this, &AProjektCharacterBase::StopShoot);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AProjektCharacterBase::InteractPressed);

	PlayerInputComponent->BindAxis("MoveForward", this, &AProjektCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProjektCharacterBase::MoveRight);
}

void AProjektCharacterBase::OnInteract(AActor* Caller)
{
	
}

void AProjektCharacterBase::StartFocus()
{
}

void AProjektCharacterBase::EndFocus()
{
}
