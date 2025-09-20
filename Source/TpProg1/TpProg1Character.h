// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once // Evita que el header se incluya varias veces en el mismo archivo de compilacion
#include "CoreMinimal.h" // Incluye las cabeceras basicas y tipos esenciales de Unreal Engine
#include "GameFramework/Character.h" // Incluye la clase base ACharacter que proporciona funcionalidad de personaje jugable
#include "Logging/LogMacros.h"// Incluye macros para crear categorias de log (mensajes de depuracion)
#include "TpProg1Character.generated.h"// Genera codigo adicional necesario para el sistema de reflection y blueprints de Unreal
class USpringArmComponent;// Declaracion adelantada de la clase USpringArmComponent (brazo de camara)
class UCameraComponent;// Declaracion adelantada de la clase UCameraComponent (camara)
class UInputAction;// Declaracion adelantada de la clase UInputAction (acciones de entrada)
struct FInputActionValue;// Declaracion adelantada de la estructura FInputActionValue (valor de entrada de una accion)

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);// Declara una categoria de log externa llamada LogTemplateCharacter para depuracion


UCLASS(abstract)// Macro que define esta clase como un UCLASS abstracta

class ATpProg1Character : public ACharacter// Declaracion de la clase ATpProg1Character que hereda de ACharacter
{
	// Macro que genera codigo necesario para reflection, serializacion y blueprint
	GENERATED_BODY()

	// Componente SpringArm que posiciona la camara detras del personaje, visible en editor, solo lectura en blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	// Componente de camara que sigue al personaje, visible en editor, solo lectura en blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

protected:
	// Accion de entrada para saltar, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	// Accion de entrada para moverse, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	// Accion de entrada para mirar/cambiar camara, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	// Accion de entrada especifica para mirar con mouse, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	// Accion de entrada para mostrar mensajes, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MostrarMensajeAction;

	// Accion de entrada para impulso, editable en editor
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AplicarImpulsoAction;

	// Accion de agrandar
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AgrandarAction;


public:
	ATpProg1Character();// Constructor de la clase

protected:
	// Funcion que inicializa el mapeo de entradas del jugador, override de ACharacter
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Funcion que se llama cuando hay entrada de movimiento
	void Move(const FInputActionValue& Value);

	// Funcion que se llama cuando hay entrada de mirar/camara
	void Look(const FInputActionValue& Value);

public:
	// Funcion blueprint-callable para mover el personaje, puede ser llamada desde UI o controles
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	// Funcion blueprint-callable para mirar/cambiar camara
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	// Funcion blueprint-callable para iniciar salto
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	// Funcion blueprint-callable para terminar salto
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

	// Funcion blueprint-callable para mostrar mensajes
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMostrarMensaje();

	// Funcion blueprint-callable para cambiar el tamanio
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAgrandar();

	// Funcion blueprint-callable para realizar un salto extra
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoAplicarImpulso();

public:
	// Funcion inline que devuelve el puntero al CameraBoom
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Funcion inline que devuelve el puntero al FollowCamera
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
