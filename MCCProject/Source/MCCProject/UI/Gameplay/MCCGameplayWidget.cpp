// Fill out your copyright notice in the Description page of Project Settings.


#include "MCCGameplayWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "KillNotify/MCCKillNotifyWidget.h"
#include "MCCProject/Core/MCCGSGameplay.h"
#include "MCCProject/Core/MCCPSGameplay.h"


void UMCCGameplayWidget::UpdateScoreboard()
{
	if (VBPlayerScoreboard)
	{
		VBPlayerScoreboard->ClearChildren();
		
		if (const auto GSGameplay = Cast<AMCCGSGameplay>(GetWorld()->GetGameState()))
		{
			for (const auto PS : GSGameplay->PlayerArray)
			{
				if (const auto PSGameplay = Cast<AMCCPSGameplay>(PS))
				{
					if (UTextBlock* TextBlockWidget = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()))
					{
						if (const auto VBChild = VBPlayerScoreboard->AddChildToVerticalBox(TextBlockWidget))
						{
							VBChild->SetHorizontalAlignment(HAlign_Fill);
							VBChild->SetVerticalAlignment(VAlign_Top);
						}
						TextBlockWidget->SetText(FText::FromString(PSGameplay->GetPlayerName() + " Kill:" + FString::FromInt(PSGameplay->GetPlayerKillScore()) + " Death:" + FString::FromInt(PSGameplay->GetPlayerDeathScore())));
					}
				}
			}
		}
	}
}


void UMCCGameplayWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
	if (ProgressBarHealth)
	{
		ProgressBarHealth->SetPercent(CurrentHealth / MaxHealth);

		const ESlateVisibility Visibility = CurrentHealth <= 0.f ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
		if (ProgressBarHealth->GetVisibility() != Visibility)
		{
			ProgressBarHealth->SetVisibility(Visibility);
		}
	}
}


void UMCCGameplayWidget::BindOnPlayerKillNotify()
{
	if (const auto GSGameplay = Cast<AMCCGSGameplay>(GetWorld()->GetGameState()))
	{
		GSGameplay->OnReceiveKill.AddDynamic(this,&UMCCGameplayWidget::OnReceiveKillNotify);
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("GSGameplay is nullptr"));
	}
}


void UMCCGameplayWidget::OnReceiveKillNotify(APlayerState* Killer, APlayerState* Victim)
{
	if (KillNotifyWidget)
	{
		KillNotifyWidget->OnReceiveKillNotify(Killer , Victim);
	}
	UpdateScoreboard();
}


void UMCCGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle , [this]()
	{
		BindOnPlayerKillNotify();
		UpdateScoreboard();
	}, 0.5f, false);
}
