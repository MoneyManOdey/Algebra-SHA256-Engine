#!/usr/bin/env bash
# start_dashboard.sh
# Copy and launch the BitcoinSSD dashboard from the mounted Volume

BITCOINSSD_VOLUME="/Volumes/BitcoinSSD"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d "$BITCOINSSD_VOLUME" ]; then
  echo "Error: Volume $BITCOINSSD_VOLUME not mounted." >&2
  exit 1
fi

echo "Syncing dashboard code to $BITCOINSSD_VOLUME..."
rsync -a --delete "$SCRIPT_DIR/Source/BitcoinSSD" "$BITCOINSSD_VOLUME/Source/"
rsync -a --delete "$SCRIPT_DIR/Config" "$BITCOINSSD_VOLUME/Config/"
rsync -a --delete "$SCRIPT_DIR/sha256_cat_collapse.py" "$BITCOINSSD_VOLUME/Scripts/"
if ls "$SCRIPT_DIR"/*.uproject > /dev/null 2>&1; then
  rsync -a --delete "$SCRIPT_DIR"/*.uproject "$BITCOINSSD_VOLUME/"
else
  echo "Warning: no .uproject files found in $SCRIPT_DIR; please ensure BitcoinSSD.uproject is present."
fi

echo "Launching dashboard..."
cd "$BITCOINSSD_VOLUME"
./Source/BitcoinSSD/launch_dashboard.sh
