// Shoot Them Up game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

    // Mapping Context for player movement
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    // Input Action for player movement
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    // Input Action for player looking
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    // Input Action for player jumping
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    // Input Action for player running
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* RunAction;

public:
    // Sets default values for this character's properties
    ASTUBaseCharacter();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
    float RunSpeed = 1200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
    float WalkSpeed = 600.f;

    UFUNCTION(BlueprintCallable, Category = "Character")
    virtual bool IsRunning() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called when moving action is triggered
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartRun(const FInputActionValue& Value);
    void EndRun(const FInputActionValue& Value);

    bool ChracterRun = false;

public:
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void SetChracterRunning(bool IsRunning) { ChracterRun = IsRunning; }
};