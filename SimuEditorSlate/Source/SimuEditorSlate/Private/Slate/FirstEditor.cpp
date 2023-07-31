#include "FirstEditor.h"
#include "FirstCommands.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "SlateColorBrush.h"

#define LOCTEXT_NAMESPACE "FirstEditor"
 FirstEditor::FirstEditor()
{
	 //注册命令
	 FFirstCommands::Register();

	 CommandList = MakeShareable(new FUICommandList);
	 //添加命令动作

	 CommandList->MapAction(FFirstCommands::Get().OpenFileCommand,
		 FExecuteAction::CreateLambda([]() {
		 FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString("OpenFileCommand"));
		 }
		 )
	 );
	 CommandList->MapAction(FFirstCommands::Get().CloseFileCommand,
		 FExecuteAction::CreateLambda([]() {
			 FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString("CloseFileCommand"));
			 }
		 )
	 );
	 CommandList->MapAction(FFirstCommands::Get().SaveFileCommand,
		 FExecuteAction::CreateLambda([]() {
			 FMessageDialog::Open(EAppMsgType::OkCancel, FText::FromString("SaveFileCommand"));
			 }
		 )
	 );



	//创建一个FTabManager
	TArray<FName>TabName = { "LeftTab","RightTopTab","RightBottomTab" };

	static FSlateColorBrush ColorBrush = FSlateColorBrush(FLinearColor(23, 45, 63, 1));
	static FSlateColorBrush ColorBrushQ = FSlateColorBrush(FLinearColor(0.0f,0.0f,0.0f,1.0f));
	FGlobalTabmanager::Get()->RegisterTabSpawner(TabName[0], FOnSpawnTab::CreateLambda(
		[&](const FSpawnTabArgs& Args)->TSharedRef<SDockTab> {
			return SNew(SDockTab)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
				.AutoHeight()
				[
					//放置菜单
					MakeMenuBar()
				]
			+ SVerticalBox::Slot()
				.AutoHeight()
				[
					//放置工具条
					MakeToolBar()

				]
				+ SVerticalBox::Slot()
				.FillHeight(1.f)
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
					[
						//颜色填充
						SNew(SBorder)
						.BorderImage(&ColorBrush)
					]
				+ SVerticalBox::Slot()
					[	//图像填充
						SNew(SBorder)
						.BorderImage(FCoreStyle::Get().GetBrush("TrashCan"))
					]
				+ SVerticalBox::Slot()
					[
						//Box填充（九宫格）
						SNew(SBorder)
						.BorderImage(FCoreStyle::Get().GetBrush("Debug.Border"))
					]
					
					]
					
				];

		}));
	FGlobalTabmanager::Get()->RegisterTabSpawner(TabName[1], FOnSpawnTab::CreateLambda(
		[&](const FSpawnTabArgs& Args)->TSharedRef<SDockTab> {
			return SNew(SDockTab)
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
				[
					SAssignNew(EditableText, SEditableText)
					
				]
			+ SVerticalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromName(TabName[1]))
					.OnClicked_Lambda(
					[&]() {
						FMessageDialog::Open(EAppMsgType::OkCancel, EditableText->GetText());
						return FReply::Handled();
					})
				]

			+ SVerticalBox::Slot()
				[
					SNew(SButton)
					.Text(FText::FromName(TabName[1]))
					.OnClicked_Lambda(
					[&]() 
					{
						TSharedPtr<SNotificationItem>CompileNotificationPtr;
						FNotificationInfo Info(NSLOCTEXT("MainFrame", "RecompileInProgress", "Compiling C++ Code"));
						//Info.Image = FCoreStyle::Get().GetBrush("TrashCan");
						Info.ExpireDuration = 5.0f;
						Info.bFireAndForget = false;
						// We can only show the cancel button on async builds
						CompileNotificationPtr = FSlateNotificationManager::Get().AddNotification(Info);
						CompileNotificationPtr.Get()->Fadeout();
						return FReply::Handled();
					})
				]
			
				];

		}));
	FGlobalTabmanager::Get()->RegisterTabSpawner(TabName[2], FOnSpawnTab::CreateLambda(
		[&](const FSpawnTabArgs& Args)->TSharedRef<SDockTab> {
			return SNew(SDockTab)
				[
					SNew(SSplitter)//分隔控件
					+SSplitter::Slot()
				.Value(2.0f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					
					[
						SNew(SBorder)
						.BorderImage(&ColorBrushQ)
						[
							SNew(STextBlock)
							.Text(FText::FromString("1-Layer"))
						]
					]
					+ SOverlay::Slot()
					[
						SNew(SBorder)
						.BorderImage(&ColorBrushQ)
						[
							SNew(STextBlock)
							.Text(FText::FromString("2-Layer"))
						]
					]
					+ SOverlay::Slot()
						[
							SNew(SBorder)
							.BorderImage(&ColorBrushQ)
						[
							SNew(STextBlock)
							.Text(FText::FromString("3-Layer"))
						]
						]
				]
					+ SSplitter::Slot()
					.Value(1.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("3-Layer"))
				]
				];

		}));
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(TEXT("Layout"))
		->AddArea(
			FTabManager::NewArea(800, 600)
			->SetOrientation(EOrientation::Orient_Horizontal)
			->Split(
				FTabManager::NewStack()
				->AddTab(TabName[0], ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewSplitter()
				->SetOrientation(EOrientation::Orient_Vertical)
				->Split(
					FTabManager::NewStack()
					->AddTab(TabName[1], ETabState::OpenedTab)
				)
				->Split(
					FTabManager::NewStack()
					->AddTab(TabName[2], ETabState::OpenedTab)
				)
			)

		);
	FGlobalTabmanager::Get()->RestoreFrom(Layout, TSharedPtr<SWindow>());
}

 TSharedRef<SWidget> FirstEditor::MakeMenuBar()
 {
	 FMenuBarBuilder MenuBuilder(CommandList);
	 MenuBuilder.AddPullDownMenu(
		 LOCTEXT("Menu1", "MyMenu"),
		 LOCTEXT("Menu1", "MyMenu"),
		 FNewMenuDelegate::CreateLambda([](FMenuBuilder& MenuBuilder) {
			 MenuBuilder.AddMenuEntry(FFirstCommands::Get().OpenFileCommand);
			 MenuBuilder.AddMenuEntry(FFirstCommands::Get().CloseFileCommand);
			 MenuBuilder.AddMenuEntry(FFirstCommands::Get().SaveFileCommand);
			 }
		 ));
	 return MenuBuilder.MakeWidget();
 }

 TSharedRef<SWidget> FirstEditor::MakeToolBar()
 {
	 FToolBarBuilder ToolBarBuilder(CommandList, FMultiBoxCustomization::None);
	 ToolBarBuilder.BeginSection("MySection");
	 ToolBarBuilder.AddToolBarButton(FFirstCommands::Get().OpenFileCommand);
	 ToolBarBuilder.AddToolBarButton(FFirstCommands::Get().CloseFileCommand);
	 ToolBarBuilder.AddToolBarButton(FFirstCommands::Get().SaveFileCommand);
	 ToolBarBuilder.EndSection();

	 return ToolBarBuilder.MakeWidget();
 }


#undef LOCTEXT_NAMESPACE