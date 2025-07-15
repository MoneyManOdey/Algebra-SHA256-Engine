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

echo "Launching dashboard..."
cd "$BITCOINSSD_VOLUME"
./Source/BitcoinSSD/launch_dashboard.sh
