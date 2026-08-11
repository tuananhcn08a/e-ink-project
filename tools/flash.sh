#!/usr/bin/env bash
# Build + flash + monitor an E-Ink firmware sketch onto the ESP32.
#
# Usage:
#   tools/flash.sh <sketch-dir> [port]
#   tools/flash.sh firmware/eink_selftest_7in5
#   tools/flash.sh firmware/eink_selftest_4in2 /dev/cu.usbserial-10
#
# Env:
#   FQBN  - board id (default esp32:esp32:esp32)
#   MON   - set MON=0 to skip the serial monitor after upload
set -euo pipefail

export PATH="/opt/homebrew/bin:$PATH"

SKETCH="${1:?usage: flash.sh <sketch-dir> [port]}"
FQBN="${FQBN:-esp32:esp32:esp32}"

# Auto-detect the ESP32 serial port if not given.
PORT="${2:-}"
if [[ -z "$PORT" ]]; then
  PORT="$(ls /dev/cu.usbserial-* /dev/cu.SLAB_USBtoUART /dev/cu.wchusbserial* 2>/dev/null | head -1 || true)"
fi
if [[ -z "$PORT" ]]; then
  echo "!! No ESP32 serial port found. Plug in the board or pass one explicitly." >&2
  exit 1
fi

echo ">> Sketch : $SKETCH"
echo ">> Board  : $FQBN"
echo ">> Port   : $PORT"

echo ">> Compiling..."
arduino-cli compile --fqbn "$FQBN" "$SKETCH"

echo ">> Uploading..."
arduino-cli upload --fqbn "$FQBN" --port "$PORT" "$SKETCH"

echo ">> Upload OK."
if [[ "${MON:-1}" == "1" ]]; then
  echo ">> Serial monitor (Ctrl-C to exit)..."
  arduino-cli monitor --port "$PORT" --config baudrate=115200
fi
