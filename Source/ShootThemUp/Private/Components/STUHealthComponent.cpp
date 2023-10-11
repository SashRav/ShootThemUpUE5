// Shoot Them Up game, All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
    }
}

void USTUHealthComponent::OnTakeAnyDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(AutoHealEnabledHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }

    if (IsAutoHeal)
        GetWorld()->GetTimerManager().SetTimer(
            AutoHealEnabledHandle, this, &USTUHealthComponent::EnableAutoHeal, AutoHealTick, true, AutoHealDelay);
}

void USTUHealthComponent::EnableAutoHeal()
{
    SetHealth(Health + AutoHealModifire);

    if (FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
        GetWorld()->GetTimerManager().ClearTimer(AutoHealEnabledHandle);
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

