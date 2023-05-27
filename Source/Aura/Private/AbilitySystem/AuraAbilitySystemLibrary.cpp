// Copyright Reaper XeS


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
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
