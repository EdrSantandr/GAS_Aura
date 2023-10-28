// Copyright Eder


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);
	
	for(auto& Pair:AS->TagsToAttributes)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		// This line executes the delegate in the TMAP, () => this replace the execution because we are using function pointers
		FGameplayAttribute Attribute = Pair.Value();
		Info.AttributeValue = Attribute.GetNumericValue(AS);
		AttributeInfoSignature.Broadcast(Info);
	}
}
