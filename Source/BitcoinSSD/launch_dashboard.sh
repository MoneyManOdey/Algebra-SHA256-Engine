#!/usr/bin/env bash
# One‑step launcher for the BitcoinSSD dashboard
# Edit UE_PROJECT/UE_EDITOR or set UE_PROJECT/UE_EDITOR env vars

UE_PROJECT="${UE_PROJECT:-$(pwd)/YourProject.uproject}"
UE_EDITOR="${UE_EDITOR:-/path/to/UnrealEditor}"  # e.g. /path/to/UnrealEngine/Engine/Binaries/Linux/UnrealEditor"

if [ ! -f "$UE_PROJECT" ]; then
    echo "Error: UE_PROJECT not found: $UE_PROJECT"
    exit 1
fi
if [ ! -x "$UE_EDITOR" ]; then
    echo "Error: UnrealEditor not found or not executable: $UE_EDITOR"
    exit 1
fi

echo "Launching BitcoinSSD Dashboard..."
exec "$UE_EDITOR" "$UE_PROJECT" -game -log
