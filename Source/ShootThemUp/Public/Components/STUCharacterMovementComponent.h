// Shoot Them Up game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    // Sets Character Max running speed
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Movement", meta=(ClampMin = "0.0", ClampMax = "3000.0"))
    float RunSpeed = 1200.f;

    // Sets Character Max walking speed
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Movement", meta = (ClampMin = "0.0", ClampMax = "3000.0"))
    float WalkSpeed = 600.f;

    virtual float GetMaxSpeed() const override;
};
