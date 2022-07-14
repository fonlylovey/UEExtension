// Fill out your copyright notice in the Description page of Project Settings.
#include "TSUserWidget.h"
#include "TSWidgetPrivate.h"


UTSUserWidget::UTSUserWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	TSClass = nullptr;
	UMGTypeScript = nullptr;
}

void UTSUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UTSUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CreateTSScript();
}

void UTSUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
	TSClass = nullptr;
	if (UMGTypeScript != nullptr)
	{
		UMGTypeScript->Destory();
		UMGTypeScript->MarkPendingKill();
		UMGTypeScript = nullptr;
	}
}

void UTSUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (UMGTypeScript != nullptr)
	{
		UMGTypeScript->Tick(InDeltaTime);
	}
}

void UTSUserWidget::CreateTSScript()
{
	if (TSClass != nullptr)
	{
		UMGTypeScript = NewObject<UTSWidgetPrivate>(this, TSClass.Get());
		UMGTypeScript->SetupUI(this);
	}
}

void UTSUserWidget::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	if (TSClass != nullptr)
	{
		UMGTypeScript = NewObject<UTSWidgetPrivate>(this, TSClass.Get());
		UMGTypeScript->SetupUI(this);
	}
}

