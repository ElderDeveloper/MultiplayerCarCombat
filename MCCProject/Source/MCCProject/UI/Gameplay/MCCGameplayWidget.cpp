// Fill out your copyright notice in the Description page of Project Settings.


#include "MCCGameplayWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "KillNotify/MCCKillNotifyWidget.h"
#include "MCCProject/Core/MCCGSGameplay.h"
#include "MCCProject/Core/MCCPSGameplay.h"
#include "SlateCore/Public/Fonts/SlateFontInfo.h"


void UMCCGameplayWidget::UpdateScoreboard()
{
	if (VBPlayerScoreboard)
	{
		VBPlayerScoreboard->ClearChildren();

		for (const auto PS : GetWorld()->GetGameState()->PlayerArray)
		{
			if (const auto PSGameplay = Cast<AMCCPSGameplay>(PS))
			{
				UTextBlock* TextBlockWidget = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
					
				FSlateFontInfo NewFont = TextBlockWidget->GetFont();
				NewFont.Size = 11;;
				TextBlockWidget->SetFont(NewFont);
					
				const auto VBChild = VBPlayerScoreboard->AddChildToVerticalBox(TextBlockWidget);
				VBChild->SetHorizontalAlignment(HAlign_Fill);
				VBChild->SetVerticalAlignment(VAlign_Top);
			
				TextBlockWidget->SetText(FText::FromString(PSGameplay->GetPlayerName() + " Kill:" + FString::FromInt(PSGameplay->GetPlayerKillScore()) + " Death:" + FString::FromInt(PSGameplay->GetPlayerDeathScore())));
			}
		}
	}
}


void UMCCGameplayWidget::BindGameStateDelegates()
{
	if (const auto GSGameplay = Cast<AMCCGSGameplay>(GetWorld()->GetGameState()))
	{
		GSGameplay->OnReceiveKill.AddDynamic(this,&UMCCGameplayWidget::OnReceiveKillNotify);
		UE_LOG(LogTemp,Log,TEXT("OnReceiveKill binding complete"));
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
	
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle , [this]()
	{
		UpdateScoreboard();
	}, 0.1f, false);
	
}


void UMCCGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameState = GetWorld()->GetGameState();

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle , [this]()
	{
		BindGameStateDelegates();
		UpdateScoreboard();
	}, 0.5f, false);
}

void UMCCGameplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GameState)
	{
		if (GameState->PlayerArray.Num() != VBPlayerScoreboard->GetChildrenCount())
		{
			UpdateScoreboard();
		}
	}
}
