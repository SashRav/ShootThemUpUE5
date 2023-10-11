// Shoot Them Up game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable)
    bool IsDead() { return FMath::IsNearlyZero(Health); }

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal")
    bool IsAutoHeal = false;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal", meta = (ClampMin = "0.0", ClampMax = "100.0", EditCondition = "IsAutoHeal"))
    float AutoHealDelay = 3.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
        meta = (ClampMin = "0.0", ClampMax = "1000.0", EditCondition = "IsAutoHeal"))
    float AutoHealModifire = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AutoHeal",
        meta = (ClampMin = "0.0", ClampMax = "1000.0", EditCondition = "IsAutoHeal"))
    float AutoHealTick = 0.5f;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void EnableAutoHeal();
    void SetHealth(float NewHealth);

    FTimerHandle AutoHealEnabledHandle;
};
