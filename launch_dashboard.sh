#!/usr/bin/env bash
# launch_dashboard.sh: One‑step launcher for the BitcoinSSD dashboard
# Set UE_PROJECT and UE_EDITOR in your environment, or edit below:
UE_PROJECT="$(pwd)/YourProject.uproject"
UE_EDITOR="/path/to/UnrealEditor"

if [ ! -f "$UE_PROJECT" ]; then
    echo "Error: UE_PROJECT not found: $UE_PROJECT"
    exit 1
fi
if [ ! -x "$UE_EDITOR" ]; then
    echo "Error: UnrealEditor not found or not executable: $UE_EDITOR"
    exit 1
fi

echo "Launching GhostMint Dashboard..."
exec "$UE_EDITOR" "$UE_PROJECT" -game -log
