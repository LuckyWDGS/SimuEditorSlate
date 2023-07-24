#include "SimuEditorSlateBPF.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SimuEditorSlate.h"
#include "Kismet/BlueprintPathsLibrary.h"
#include "UnrealExtensionsBPFLibrary.h"

#define LOCTEXT_NAMESPACE "SimuEditorSlateBPF"

TArray<FSlateMapData> USimuEditorSlateBPF::LoadMapToFind(FString FindDirectoryPath, FString Substring,bool NotContains, int32 TypeMap)
{
	FSlateMapData temporary;
	TArray<FSlateMapData> Maps;
	TArray<FString> Directorys;
	FFileData FileData;
	UUnrealExtensionsBPFLibrary::FindDirectory(FindDirectoryPath, Directorys);
	for (auto Dorectory : Directorys) {
		
		if (UKismetStringLibrary::Contains(UBlueprintPathsLibrary::GetBaseFilename(Dorectory), Substring)|| NotContains) {
			UUnrealExtensionsBPFLibrary::GetStatData(Dorectory, FileData);
			temporary.MapName = UBlueprintPathsLibrary::GetBaseFilename(Dorectory);
			temporary.ModificationTime = GetDataTime(FileData.ModificationTime);
			temporary.DirectoryPath = Dorectory;
			temporary.TypeMap = TypeMap;
			Maps.Add(temporary);
		}
	}
	return Maps;
}

FString USimuEditorSlateBPF::SelectedTime(int32 Param)
{
	if (Param > 9) {
		return FString::FromInt(Param);
	}
	return "0" + FString::FromInt(Param);
}

FString USimuEditorSlateBPF::GetDataTime(FDateTime DateTime)
{
	
	//输出的格式 2023-06-14  11:41  Hour+8为北京时区
	return FString::FromInt(DateTime.GetYear()) + "-" + SelectedTime(DateTime.GetMonth()) + "-" + SelectedTime(DateTime.GetDay()) + "  " + SelectedTime(DateTime.GetHour()+8) + ":" + SelectedTime(DateTime.GetMinute());
}


#undef LOCTEXT_NAMESPACE

void UConnectionMap::Activate()
{
		FSimuEditorSlateModule& SimuEditorSlateModule = FModuleManager::LoadModuleChecked<FSimuEditorSlateModule>("SimuEditorSlate");
		SimuEditorSlateModule.ConntectionMap = this;
		SimuEditorSlateModule.AssociatedMap();

}

void UOpenTheApps::Activate()
{
	FSimuEditorSlateModule& SimuEditorSlateModule = FModuleManager::LoadModuleChecked<FSimuEditorSlateModule>("SimuEditorSlate");
	SimuEditorSlateModule.OpenTheApp = this;
	SimuEditorSlateModule.OpenTheApps();

}

void UApplication::Activate()
{
	FSimuEditorSlateModule& SimuEditorSlateModule = FModuleManager::LoadModuleChecked<FSimuEditorSlateModule>("SimuEditorSlate");
	SimuEditorSlateModule.Application = this;
	SimuEditorSlateModule.Applications();
}

void UFinishComplete::Activate()
{
	FSimuEditorSlateModule& SimuEditorSlateModule = FModuleManager::LoadModuleChecked<FSimuEditorSlateModule>("SimuEditorSlate");
	SimuEditorSlateModule.FinishComplete = this;
	SimuEditorSlateModule.FinishWizard();

}

void UInitApps::Activate()
{
	FSimuEditorSlateModule& SimuEditorSlateModule = FModuleManager::LoadModuleChecked<FSimuEditorSlateModule>("SimuEditorSlate");
	SimuEditorSlateModule.InitTheApp = this;
	SimuEditorSlateModule.InitApps();
}

void UDelay::DelayEvent()
{
	OnCompleted.Broadcast();
}

void UDelay::Activate()
{
	GEditor->GetTimerManager()->SetTimer(TimerHandle, this, &UDelay::DelayEvent, DelayTimer, false);
}
