// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "SpaceProjectile.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Cache our sound effect
	//static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	//FireSound = FireAudio.Object;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MoveSpeed = 2;
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
	//bFireContinue = 0;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);

	// Set up "action" bindings.
	PlayerInputComponent->BindAxis("Fire", this, &AMyPlayer::FireShot);
	//PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyPlayer::StopFireShot);
}

void AMyPlayer::MoveForward(float Value)
{
	if (Value)
	{
		Value = Value * MoveSpeed;
		AddMovementInput(GetActorForwardVector(), Value);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MoveRight - %f"), Value));
	}
}

void AMyPlayer::MoveRight(float Value)
{
	if (Value)
	{
		Value = Value * MoveSpeed;
		AddMovementInput(GetActorRightVector(), Value);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MoveForward - %f"), Value));
	}
}

void AMyPlayer::FireShot(float Value)
{
	if (Value)
	{
		// If it's ok to fire again
		if (bCanFire == true)
		{
			const FRotator FireRotation;
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<ASpaceProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMyPlayer::ShotTimer, FireRate);

			// try and play the sound if specified
			//if (FireSound != nullptr)
			//{
			//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			//}

			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fire value %f"),Value));
		}
		//bFireContinue = 3;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fire p ")));
	}

}

void AMyPlayer::ShotTimer()
{
	bCanFire = true;
}