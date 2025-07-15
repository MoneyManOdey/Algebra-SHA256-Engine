#!/bin/bash

# Set path to Unreal Editor
export UE_EDITOR="/Users/Shared/UnrealEngine/UE_5.4/Engine/Binaries/Mac/UnrealEditor"

# Set the correct project path based on actual location
export UE_PROJECT="/Users/oliverodusanya/aci_pow/BitcoinSSD.uproject"
# Generate module boilerplate if missing
MODULE_DIR="$(dirname "$UE_PROJECT")/Source/BitcoinSSD"
if [ ! -f "$MODULE_DIR/BitcoinSSD.Build.cs" ] || [ ! -f "$MODULE_DIR/Private/BitcoinSSD.cpp" ]; then
  echo "Generating missing BitcoinSSD module boilerplate..."
  mkdir -p "$MODULE_DIR/Private"
  cat > "$MODULE_DIR/BitcoinSSD.Build.cs" << 'CS'
using UnrealBuildTool;

public class BitcoinSSD : ModuleRules
{
    public BitcoinSSD(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore"
        });
    }
}
CS

  cat > "$MODULE_DIR/Private/BitcoinSSD.cpp" << 'CPP'
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, BitcoinSSD, "BitcoinSSD");
CPP
fi

# Launch Unreal Engine with the correct project
"$UE_EDITOR" "$UE_PROJECT" -game -log
