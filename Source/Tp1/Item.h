// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TP1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Nombre del objeto */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Properties")
	FString ItemName;

	/** Rareza del objeto (Común, Raro, Épico, etc.) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties")
	FString ItemTier;

	/** Puntos de vida que otorga o afecta */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	int32 LifeBonus;

	/** Puntos de experiencia que otorga al recolectarlo */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Properties")
	int32 XPReward;

	/** Durabilidad del objeto (0 - 100) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", 
		meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0", ToolTip = "Durability of the item"))
	float DurabilityValue;

};
