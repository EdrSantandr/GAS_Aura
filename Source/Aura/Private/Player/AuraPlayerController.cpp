// Copyright Eder


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent =CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	// a) Lastactor == null and ThisActor==null -> Do nothing

	// b) Lastactor == null and ThisActor is valid -> Do Highligth ThisActor

	// c) Lastactor is valid and ThisActor == null -> Do Unhighligth LastActor
	
	// d) Lastactor is valid and ThisActor is valid, but LastActor != ThisActor -> Do Unhighligth LastActor, and Hightlight ThisActor

	// e) Lastactor is valid and ThisActor is valid, but LastActor == ThisActor -> Do nothing

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case b)
			ThisActor->HighlightActor();
		}
		else
		{
			//Case a)
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			//Case c)
			LastActor->UnHighlightActor();
		}
		else // BothActors are valid
		{
			if (LastActor != ThisActor)
			{
				//Case d)
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//Case e)
			}
		}
	}
}
