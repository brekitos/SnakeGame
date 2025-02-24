// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"


// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;


}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(-90, 0, 0));
	CreateSnakeActor();
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePLayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);

}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APlayerPawnBase::HandlePLayerVerticalInput(float value)
{
	
	if (IsValid(SnakeActor) && SnakeActor->CanMove == false)
	{
		if (value > 0 && SnakeActor->LastMovementDirection!=EMovementDirection::DOWN)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::UP;
			SnakeActor->CanMove = true;
		}
		else if (value < 0 && SnakeActor->LastMovementDirection!=EMovementDirection::UP)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::DOWN;
			SnakeActor->CanMove = true;
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	
	if (IsValid(SnakeActor) && SnakeActor->CanMove == false)
	{
		if (value > 0 && SnakeActor->LastMovementDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::RIGHT;
			SnakeActor->CanMove = true;
		}
		else if (value < 0 && SnakeActor->LastMovementDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::LEFT;
			SnakeActor->CanMove = true;
		}
	}
}