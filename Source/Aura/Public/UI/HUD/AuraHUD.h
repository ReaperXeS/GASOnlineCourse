// Copyright Reaper XeS

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAuraUserWidget;
class UAttributeSet;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& InWidgetControllerParams);

	void InitOverlay(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet);
private:
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	/**
	 * This is a pointer to the widget controller that is created in GetOverlayWidgetController
	 */
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	/**
	 * This is the class that is used to create the widget controller in GetOverlayWidgetController
	 */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	// This is a pointer to the widget controller that is created in GetAttributeMenuWidgetController
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	// This is the class that is used to create the widget controller in GetAttributeMenuWidgetController
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
