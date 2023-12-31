// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Widgets/SWindow.h"

/** This is a custom dialog class, which allows any Slate widget to be used as the contents,
 * with any number of buttons that have any text. 
 * It also supports adding a custom icon to the dialog.
 * Usage:
 * TSharedRef<SCustomDialog> HelloWorldDialog = SNew(SCustomDialog)
		.Title(FText(LOCTEXT("HelloWorldTitleExample", "Hello, World!")))
		.DialogContent( SNew(SImage).Image(FName(TEXT("Hello"))))
		.Buttons({
			SCustomDialog::FButton(LOCTEXT("OK", "OK")),
			SCustomDialog::FButton(LOCTEXT("Cancel", "Cancel"))
		});

   // returns 0 when OK is pressed, 1 when Cancel is pressed, -1 if the window is closed
   const int ButtonPressed = HelloWorldDialog->ShowModal();
 */
class  SFirstCustomDialog : public SWindow
{
public:
	struct FButton
	{
		FButton(const FText& InButtonText, const FSimpleDelegate& InOnClicked = FSimpleDelegate())
			: ButtonText(InButtonText),
			OnClicked(InOnClicked)
		{
		}

		FText ButtonText;
		FSimpleDelegate OnClicked;
	};

	SLATE_BEGIN_ARGS(SFirstCustomDialog)
		: _UseScrollBox(true)
		, _ScrollBoxMaxHeight(300)
	{
		_AccessibleParams = FAccessibleWidgetData(EAccessibleBehavior::Auto);
	}
		/** Title to display for the dialog. */
		SLATE_ARGUMENT(FText, Title)

		/** How the window should be sized */
		SLATE_ARGUMENT(ESizingRule, SizingRule)

		/** Screen-space position where the window should be initially located. */
		SLATE_ARGUMENT(FVector2D, ScreenPosition)

		/** What the initial size of the window should be. */
		SLATE_ARGUMENT(FVector2D, ClientSize)

		/** Optional icon to display in the dialog. (default: none) */
		SLATE_ARGUMENT(FName, IconBrush)

		/** Should this dialog use a scroll box for over-sized content? (default: true) */
		SLATE_ARGUMENT(bool, UseScrollBox)

		/** Max height for the scroll box (default: 300) */
		SLATE_ARGUMENT(int32, ScrollBoxMaxHeight)

		/** The buttons that this dialog should have. One or more buttons must be added.*/
		SLATE_ARGUMENT(TArray<FButton>, Buttons)

		/** Content for the dialog */
		SLATE_ARGUMENT(TSharedPtr<SWidget>, DialogContent)

		/** Event triggered when the dialog is closed, either because one of the buttons is pressed, or the windows is closed. */
		SLATE_EVENT(FSimpleDelegate, OnClosed)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	/** Show the dialog.
	 * This method will return immediately.
	 */ 
	void Show();

	/** Show a modal dialog. Will block until an input is received.
	 * Returns the index of the button that was pressed.
	 */
	int32 ShowModal();

private:
	FReply OnButtonClicked(FSimpleDelegate OnClicked, int32 ButtonIndex);

	/** The index of the button that was pressed last. */
	int32 LastPressedButton = -1;

	FSimpleDelegate OnClosed;
};