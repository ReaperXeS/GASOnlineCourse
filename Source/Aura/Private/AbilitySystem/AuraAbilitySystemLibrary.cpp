// Copyright Reaper XeS


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

bool UAuraAbilitySystemLibrary::GetAuraHudAndWidgetControllerParams(const UObject* WorldContextObject, AAuraHUD*& OutAuraHUD, FWidgetControllerParams& WidgetControllerParams)
{
	// Get Player controller
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// AuraHUD from PlayerController
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			InitWidgetControllerParams(PlayerController, PlayerState, WidgetControllerParams);
			
			// OverlayWidgetController from AuraHUD
			OutAuraHUD = AuraHUD;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	AAuraHUD* AuraHUD;
	if (FWidgetControllerParams WidgetControllerParams; GetAuraHudAndWidgetControllerParams(WorldContextObject, AuraHUD, WidgetControllerParams))
	{
		return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
	}
	
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitWidgetControllerParams(APlayerController* PlayerController, AAuraPlayerState* PlayerState, FWidgetControllerParams& WidgetControllerParams)
{
	WidgetControllerParams.PlayerController = PlayerController;
	WidgetControllerParams.PlayerState = PlayerState;
	WidgetControllerParams.AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
	WidgetControllerParams.AttributeSet = PlayerState->GetAttributeSet();
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	AAuraHUD* AuraHUD;
	if (FWidgetControllerParams WidgetControllerParams; GetAuraHudAndWidgetControllerParams(WorldContextObject, AuraHUD, WidgetControllerParams))
	{
		return AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::ApplyGameEffectFromAttributes(const float Level, UAbilitySystemComponent* AbilitySystemComponent, const AActor* AvatarActor, const TSubclassOf<UGameplayEffect> GameplayEffect)
{
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, Level, EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	check(CharacterClassInfo);

	const AActor* AvatarActor = AbilitySystemComponent->GetAvatarActor();
	ApplyGameEffectFromAttributes(Level, AbilitySystemComponent, AvatarActor, CharacterClassInfo->GetPrimaryAttributes(CharacterClass));
	ApplyGameEffectFromAttributes(Level, AbilitySystemComponent, AvatarActor, CharacterClassInfo->GetSecondaryAttributes());
	ApplyGameEffectFromAttributes(Level, AbilitySystemComponent, AvatarActor, CharacterClassInfo->GetVitalAttributes());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent)
{
	const UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	check(CharacterClassInfo);

	// Loop through Common Abilities and give them to ability system component
	for (const TSubclassOf<UGameplayAbility>& CommonAbility : CharacterClassInfo->GetCommonAbilities())
	{
		if (UGameplayAbility* Ability = CommonAbility.GetDefaultObject())
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1));
		}
	}
}

UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	if (const AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{		
		return GameMode->GetCharacterClassInfo();
	}
	return nullptr;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}
	return false;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsBlockedHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
