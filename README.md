# E-Ink Project

Experimenting with and building a touch e-ink display product on ESP32.

## Status
Phase 1 — **bring-up**. The 7.5" panel + ESP32 kit are flashing and refreshing
successfully (see `docs/hardware/bring-up.md`).

## Hardware
- **Board:** ESP32-DevKitC v4 (ESP32-WROOM-32).
- **Panels:** 4.2" (400×300) and 7.5" (640×384), both 3-color black/white/red.
- **Wiring:** CS=15, DC=27, RST=26, BUSY=25, SCK=13, MOSI=14 (see `firmware/shared/pins.h`).

## Quick start (build + flash the self-test)
```bash
# 7.5" panel
tools/flash.sh firmware/eink_selftest_7in5

# 4.2" panel
tools/flash.sh firmware/eink_selftest_4in2
```
`flash.sh` compiles, uploads (auto-detects the serial port), then opens the serial
monitor. Note: this cable needs `UploadSpeed=115200` — the helper and the docs handle it.

Prereqs (already installed on the dev Mac): `arduino-cli` + `esp32:esp32` core, the
seller's modified `GxEPD2` library, and Adafruit GFX.

## How we work
This project runs with an AI team (Coordinator + specialists + Architect gate). Read
[`CLAUDE.md`](CLAUDE.md) for the team model and workflow. Type `SESSION START` to begin.

## Layout
- `firmware/` — ESP32 sketches (`eink_selftest_*`, `shared/pins.h`)
- `tools/` — `flash.sh`
- `docs/` — research, specs, architecture, design, phases, hardware
- `services/` — content/provisioning backend (added when needed)
- `init_resources/` — seller-provided originals (don't edit)
