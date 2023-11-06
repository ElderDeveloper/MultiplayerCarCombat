// Fill out your copyright notice in the Description page of Project Settings.

#include "MCCKillNotifyWidget.h"
#include "MCCKillNotifyEntryWidget.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "MCCProject/Core/MCCPSGameplay.h"


void UMCCKillNotifyWidget::OnReceiveKillNotify(APlayerState* Killer ,APlayerState* Victim)
{
	if (KillEntryClass != nullptr)
	{
		if (const auto KillWidget = CreateWidget<UMCCKillNotifyEntryWidget>(GetOwningPlayer(),KillEntryClass))
		{
			if (const auto VBChild = VBKillNotify->AddChildToVerticalBox(KillWidget))
			{
				VBChild->SetHorizontalAlignment(HAlign_Fill);
				VBChild->SetVerticalAlignment(VAlign_Top);
			}
			KillWidget->SetupWidget(Killer , Victim);
		}
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("KillEntryClass is nullptr"));
	}
}


void UMCCKillNotifyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


bool UMCCKillNotifyWidget::Initialize()
{
	const bool Success = Super::Initialize();
	return Success;
}
