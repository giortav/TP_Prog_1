// Copyright Epic Games, Inc. All Rights Reserved.

#include "TpProg1Character.h" // Incluye el header de la clase para poder definir sus funciones
#include "Engine/LocalPlayer.h" // Permite acceder a informacion del jugador local
#include "Camera/CameraComponent.h" // Necesario para usar la camara en tercera persona
#include "Components/CapsuleComponent.h" // Necesario para usar el componente capsula (colision)
#include "GameFramework/CharacterMovementComponent.h" // Acceso al movimiento del Character
#include "GameFramework/SpringArmComponent.h" // Permite el uso del brazo de camara (CameraBoom)
#include "GameFramework/Controller.h" // Para controlar rotacion e input del jugador
#include "EnhancedInputComponent.h" // Permite el sistema de Input mejorado (Enhanced Input)
#include "EnhancedInputSubsystems.h" // Subsistema para manejar los mapeos de input
#include "InputActionValue.h" // Tipo de dato usado por Enhanced Input para manejar valores de accion
#include "TpProg1.h" // Header del proyecto (logs, defines, etc.)

// ===================== CONSTRUCTOR =====================
ATpProg1Character::ATpProg1Character()
{
    // Configura el tamano de la capsula de colision del personaje 
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Desactiva la rotacion automatica del personaje al rotar el controlador
    // Permite que solo la camara rote, no el cuerpo del Character
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configura que el personaje se oriente automaticamente hacia la direccion de movimiento
    GetCharacterMovement()->bOrientRotationToMovement = true;

    // Establece la velocidad de rotacion del personaje para seguir la direccion de movimiento
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    // Velocidad vertical al saltar (Z). 
    GetCharacterMovement()->JumpZVelocity = 500.f;

    // Control en el aire: porcentaje de movimiento que puedes aplicar mientras saltas (0�1)
    GetCharacterMovement()->AirControl = 0.35f;

    // Velocidad maxima de caminata en el suelo
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    // Velocidad minima para movimiento analogico (joystick). 
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;

    // Desaceleracion al soltar el movimiento en el suelo
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

    // Desaceleracion cuando cae. Util para ajustar la caida tras un salto
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    // Crea un "Camera Boom" (brazo de camara) para mantener la camara a una distancia del personaje
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    // Adjunta el brazo de camara al componente raiz (RootComponent del Character)
    CameraBoom->SetupAttachment(RootComponent);
    // Distancia de la camara respecto al personaje (en cm). 
    CameraBoom->TargetArmLength = 400.0f;
    // Permite que la camara rote siguiendo el control del jugador
    CameraBoom->bUsePawnControlRotation = true;

    // Crea la camara de seguimiento (FollowCamera)
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    // La camara se adjunta a la punta del CameraBoom para seguir su posicion
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    // Desactiva la rotacion automatica de la camara basada en el movimiento del personaje
    FollowCamera->bUsePawnControlRotation = false;

}

// ===================== INPUT =====================
void ATpProg1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Configura las acciones de input del jugador usando el sistema Enhanced Input
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

        // Accion de salto: al presionar -> Jump(), al soltar -> StopJumping()
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        // Accion de movimiento: recibe un vector2D de direccion (X,Y)
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATpProg1Character::Move);

        // Accion de mirar con el mouse/joystick: rota camara/Character
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATpProg1Character::Look);

        // Accion de mirar generica (puede venir de otro dispositivo)
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATpProg1Character::Look);

        // Accion de mostrar mensaje
        EnhancedInputComponent->BindAction(MostrarMensajeAction, ETriggerEvent::Started, this, &ATpProg1Character::DoMostrarMensaje);

        // Accion de cambiar velocidad
        EnhancedInputComponent->BindAction(AgrandarAction, ETriggerEvent::Started, this, &ATpProg1Character::DoAgrandar);

        // Accion de impulso extra
        EnhancedInputComponent->BindAction(AplicarImpulsoAction, ETriggerEvent::Started, this, &ATpProg1Character::DoAplicarImpulso);
    }
    else
    {
        // Mensaje de error si no se encuentra un EnhancedInputComponent
        // Sucede si intentas usar el sistema viejo de Input sin actualizar este codigo
        UE_LOG(LogTpProg1, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
    }
}

// ===================== MOVIMIENTO =====================
void ATpProg1Character::Move(const FInputActionValue& Value)
{
    // Convierte el input en un vector 2D (X = lateral, Y = adelante/atras)
    FVector2D MovementVector = Value.Get<FVector2D>();

    // Envia el input al metodo interno que aplica el movimiento real
    DoMove(MovementVector.X, MovementVector.Y);
}

void ATpProg1Character::Look(const FInputActionValue& Value)
{
    // Convierte el input en un vector 2D (X = yaw, Y = pitch)
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    // Envia el input al metodo interno que aplica la rotacion
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATpProg1Character::DoMove(float Right, float Forward)
{
    // Verifica que el personaje tenga un controlador antes de mover
    if (GetController() != nullptr)
    {
        // Obtiene la rotacion actual del controlador (camara)
        const FRotator Rotation = GetController()->GetControlRotation();
        // Crea un rotador solo con el Yaw (rotacion horizontal)
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Calcula el vector de direccion frontal (X) basado en el yaw
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        // Calcula el vector de direccion lateral (Y) basado en el yaw
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // Aplica movimiento en direccion frontal y lateral con intensidad Forward/Right
        AddMovementInput(ForwardDirection, Forward);
        AddMovementInput(RightDirection, Right);
    }
}

void ATpProg1Character::DoLook(float Yaw, float Pitch)
{
    // Verifica que el controlador exista antes de rotar
    if (GetController() != nullptr)
    {
        // Aplica rotacion horizontal (Yaw) a la camara/Character
        AddControllerYawInput(Yaw);
        // Aplica rotacion vertical (Pitch) para mirar arriba/abajo
        AddControllerPitchInput(Pitch);
    }
}

// ===================== SALTO =====================
void ATpProg1Character::DoJumpStart()
{
    // Llama a Jump() para iniciar el salto
    Jump();
}

void ATpProg1Character::DoJumpEnd()
{
    // Llama a StopJumping() para terminar el salto si se mantiene presionado
    StopJumping();
}

void ATpProg1Character::DoMostrarMensaje()
{
    // Muestra un mensaje en pantalla
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Hola Kent"));
}

void ATpProg1Character::DoAgrandar()
{
    // Alterna entre tamaño normal y tamaño aumentado
    FVector CurrentScale = GetActorScale3D();
    FVector NewScale = (CurrentScale.X > 1.0f) ? FVector(1.0f) : FVector(1.5f);
    SetActorScale3D(NewScale);
}

void ATpProg1Character::DoAplicarImpulso()
{
    // Aplica un pequeño salto extra sin depender del Jump normal
    if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
    {
        FVector Impulse = FVector(0.f, 0.f, 600.f);
        LaunchCharacter(Impulse, false, true);
    }
}
