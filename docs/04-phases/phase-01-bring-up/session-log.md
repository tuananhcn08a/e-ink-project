# Session log — phase-01-bring-up

Newest entries first.

## 2026-08-12 — Project kickoff, team + toolchain, 7.5" bring-up
**Done**
- Built the AI team (`.claude/agents/`): coordinator, pm, ba, ux-designer, firmware-dev, hardware-dev, backend-dev, qa, architect. Workflow modeled on the PO's other teams (miwiz / bap-bean-book / ta-studio-ops).
- Set up toolchain: arduino-cli + esp32 core 3.3.11 + esptool; installed seller's GxEPD2 (modified) + Adafruit GFX.
- Decoded seller wiring from demo sketches → `firmware/shared/pins.h` (CS15 DC27 RST26 BUSY25 SCK13 MOSI14).
- Wrote clean self-test sketches for 4.2" and 7.5" (both compile clean).
- Flashed 7.5" self-test to the real board. Serial confirms panel reports 640×384, full refresh completed, hibernated OK. Firmware/electrical = PASS.

**Decisions**
- Upload at 115200 baud (921600 fails on this cable). Recorded in `docs/hardware/bring-up.md`.
- Panels are 3-color (B/W/R) — designs constrained accordingly.

**Blockers**
- None. Waiting on PO to eyeball/photograph the 7.5" panel to close T-002's QA gate.

**Next 3 actions**
1. PO confirms the 7.5" test pattern looks right (photo) → close T-002.
2. Bring up the 4.2" panel (T-003): connect it, flash `eink_selftest_4in2`.
3. pm proposes the first product use-case (T-004) → ba writes the first real spec.
