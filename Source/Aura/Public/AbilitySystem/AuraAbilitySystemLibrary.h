// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Player/AuraPlayerState.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class AAuraHUD;
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool GetAuraHudAndWidgetControllerParams(const UObject* WorldContextObject, AAuraHUD*& OutAuraHUD, FWidgetControllerParams& WidgetControllerParams);
	UFUNCTION(BlueprintPure, Category = "Aura Ability System Library | Overlay Widget Controller")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	static void InitWidgetControllerParams(APlayerController* PlayerController, AAuraPlayerState* PlayerState, FWidgetControllerParams& WidgetControllerParams);

	UFUNCTION(BlueprintPure, Category = "Aura Ability System Library | Attribute Menu Widget Controller")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);
	static void ApplyGameEffectFromAttributes(float Level, UAbilitySystemComponent* AbilitySystemComponent, const AActor* AvatarActor, TSubclassOf<UGameplayEffect> GameplayEffect);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent);
};
