#!/usr/bin/env bash
# start_dashboard.sh — launch the BitcoinSSD dashboard in Unreal Editor 5.4

UE_EDITOR="/Users/Shared/UnrealEngine/UE_5.4/Engine/Binaries/Mac/UnrealEditor"
UE_PROJECT="/Users/oliverodusanya/aci_pow/BitcoinSSD/BitcoinSSD.uproject"

if [ ! -x "$UE_EDITOR" ]; then
  echo "Error: Unreal Editor not found at $UE_EDITOR" >&2
  exit 1
fi

if [ ! -f "$UE_PROJECT" ]; then
  echo "Error: Project file not found at $UE_PROJECT" >&2
  exit 1
fi

echo "Launching BitcoinSSD Dashboard..."
exec "$UE_EDITOR" "$UE_PROJECT" -game
