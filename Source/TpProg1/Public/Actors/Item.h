// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TPPROG1_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	int HealthPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	int ExperiencePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (ClampMin = "0.0", ClampMax = "100.0", UIMin = "0.0", UIMax = "100.0", ToolTip = "Durability of the item"))
	float Durability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Properties")
	FString Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FString Rarity;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
