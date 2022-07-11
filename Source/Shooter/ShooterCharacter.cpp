// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a camera boom (pulls in towards the character if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f; // Camera follows at this distance behind character
	CameraBoom->bUsePawnControlRotation = true; // Rotate arm based on controller.

	//Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); //Attaches Camera to the end of the boom
	FollowCamera->bUsePawnControlRotation = false; //Camera rotates only to boom.
	
	
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which direction is forward
		const FRotator Rotation { Controller->GetControlRotation() };
		const FRotator YawRotation {0, Rotation.Yaw, 0};
		const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X)};
		
		AddMovementInput(Direction, Value);
		
	} 
}

void AShooterCharacter::MoveRight(float Value)
{

	if (Controller != nullptr && Value != 0.0f)
	{
		// find out which direction is forward
		const FRotator Rotation { Controller->GetControlRotation() };
		const FRotator YawRotation {0, Rotation.Yaw, 0};
		const FVector  Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y)};
		
		AddMovementInput(Direction, Value);
		
	}
	
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(!PlayerInputComponent) { return; }

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);


	
}

