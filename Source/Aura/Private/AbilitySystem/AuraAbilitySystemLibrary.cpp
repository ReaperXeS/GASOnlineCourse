// Copyright Reaper XeS


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	// Get Player controller
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		// AuraHUD from PlayerController
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PlayerState = PlayerController->GetPlayerState<AAuraPlayerState>();
			FWidgetControllerParams WidgetControllerParams;
			WidgetControllerParams.PlayerController = PlayerController;
			WidgetControllerParams.PlayerState = PlayerState;
			WidgetControllerParams.AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
			WidgetControllerParams.AttributeSet = PlayerState->GetAttributeSet();
			
			// OverlayWidgetController from AuraHUD
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
