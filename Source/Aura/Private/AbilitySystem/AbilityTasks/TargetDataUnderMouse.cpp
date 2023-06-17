// Copyright Reaper XeS


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();

	// Get Player Controller from Ability
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);
	OnMouseTargetData.Broadcast(CursorHitResult.Location);
}
