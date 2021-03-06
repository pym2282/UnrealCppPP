#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRatio, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();

}
void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InAttackCauser, InOtherCharacter);
	CheckNull(InOtherCharacter);

	FDamageEvent e;
	InOtherCharacter->TakeDamage(Datas[Index].Power, e, InAttacker->GetController(), InAttackCauser);

}
void ACDoAction_Melee::OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* InAttackCauser, class ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InAttackCauser, InOtherCharacter);
}
