#include "CActionComponent.h"
#include "Global.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "GameFramework/Character.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* character = Cast<ACharacter>(GetOwner());
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if(!!Datas[i])
			Datas[i]->BeginPlay(character);
	}

}


void UCActionComponent::SetUnarmedMode()
{
	if (!!Datas[(int32)Type])
		Datas[(int32)Type]->GetEquipment()->Unequip();

	Datas[(int32)EActionType::Unarmed]->GetEquipment()->Equip();

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetFireStormMode()
{
	SetMode(EActionType::FireStorm);
}

void UCActionComponent::SetIceBallMode()
{
	SetMode(EActionType::IceBall);
}

void UCActionComponent::DoAction()
{
	CheckTrue(IsUnarmedMode());
	if (!!Datas[(int32)Type])
	{
		ACDoAction* action = Datas[(int32)Type]->GetDoAction();

		if (!!action)
			action->DoAction();
	}
}

void UCActionComponent::SetMode(EActionType InType)
{
	if (Type == InType)
	{
		SetUnarmedMode();

		return;
	}

	else if (IsUnarmedMode() == false)
	{
		if(!!Datas[(int32)Type])
			Datas[(int32)Type]->GetEquipment()->Unequip();
	}

	if (!!Datas[(int32)InType])
		Datas[(int32)InType]->GetEquipment()->Equip();

	ChangeType(InType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType prevType = Type;
	Type = InNewType;

	if (OnActionChanged.IsBound())
		OnActionChanged.Broadcast(prevType, InNewType);
}