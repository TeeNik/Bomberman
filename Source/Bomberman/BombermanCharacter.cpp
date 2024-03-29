#include "BombermanCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "BombermanGameMode.h"
#include "System/BombManager.h"
#include "Floor.h"
#include "UtilsLibrary.h"
#include "Net/UnrealNetwork.h"

ABombermanCharacter::ABombermanCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

    bReplicates = true;
}

void ABombermanCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABombermanCharacter::SetBomb);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABombermanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABombermanCharacter::MoveRight);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABombermanCharacter::OnBeginOverlap);
}


void ABombermanCharacter::ServerSetBomb_Implementation() {
    SetBomb();
}

//for future validation
bool ABombermanCharacter::ServerSetBomb_Validate() {
    return true;
}

void ABombermanCharacter::SetBomb()
{
    if (Role < ROLE_Authority) {
        ServerSetBomb();
        return;
    }

    GLog->Log(GetName());

	ABombermanGameMode* GM = Cast<ABombermanGameMode>(GetWorld()->GetAuthGameMode());
	if (GM != NULL) {
		GM->GetBombManager()->SetBomb(Floor);
	}
}

void ABombermanCharacter::OnBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(UtilsLibrary::FloorTag)) {
		AFloor* floor = Cast<AFloor>(OtherActor);
		if (floor != NULL) {
			Floor = floor;

            if (Role == ROLE_Authority)
            {
                GLog->Log(Floor->GetName());
            }
		}
	}
}

void ABombermanCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABombermanCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABombermanCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABombermanCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABombermanCharacter, Floor);
}
