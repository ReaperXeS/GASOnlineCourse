// Copyright Reaper XeS


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();

	// If locally controlled, send mouse cursor data to server
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	} else
	{
		// On Server listen for Target Data
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UTargetDataUnderMouse::SendMouseCursorData()
{
	// Begin Predicting sync between client and server
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	// Get Player Controller from Ability
	const APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHitResult;
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* TargetDataHitResult = new FGameplayAbilityTargetData_SingleTargetHit(CursorHitResult);
	TargetDataHandle.Add(TargetDataHitResult);

	AbilitySystemComponent->CallServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), TargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	// Make sure ability is still active
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnMouseTargetData.Broadcast(TargetDataHandle);	
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
	// Consumes cached TargetData from client
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnMouseTargetData.Broadcast(Data);
	}
}
