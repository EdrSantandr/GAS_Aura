// Copyright Eder


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	//Here we need to broadcast health and mana
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChangedSignature.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChangedSignature.Broadcast(AuraAttributeSet->GetMaxHealth());
}
