// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SimuEditorSlate : ModuleRules
{
	public SimuEditorSlate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"Editor/UMGEditor/Private", // For PCH includes (because they don't work with relative paths, yet)
				"Editor/UMGEditor/Private/Templates",
				"Editor/UMGEditor/Private/Extensions",
				"Editor/UMGEditor/Private/Customizations",
				"Editor/UMGEditor/Private/BlueprintModes",
				"Editor/UMGEditor/Private/TabFactory",
				"Editor/UMGEditor/Private/Designer",
				"Editor/UMGEditor/Private/Hierarchy",
				"Editor/UMGEditor/Private/Palette",
				"Editor/UMGEditor/Private/Details",
				"Editor/UMGEditor/Private/DragDrop",
				"Editor/UMGEditor/Private/Utility",
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"StandaloneRenderer",
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"InputCore",
				"Engine",
				"AssetTools",
				"UMGEditor",
				"KismetWidgets",
				"KismetCompiler",
				"BlueprintGraph",
				"GraphEditor",
				"Kismet",  // for FWorkflowCentricApplication
				"PropertyPath",
				"PropertyEditor",
				"UMG",
				"EditorStyle",
				"MessageLog",
				"MovieScene",
				"MovieSceneTools",
				"MovieSceneTracks",
				"DetailCustomizations",
				"Settings",
				"RenderCore",
				"TargetPlatform",
				"TimeManagement",
				"GameProjectGeneration",
				"PropertyPath",
				"ToolMenus",
				"SlateReflector",
				"DeveloperSettings",
				"UnrealExtensions",

		// ... add private dependencies that you statically link with here ...	
	}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
