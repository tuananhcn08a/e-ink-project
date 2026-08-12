# Hardware bring-up log

Newest entries first. This is the source of truth for verified hardware facts:
board, panels, wiring, driver classes, and diagnosis notes. Owned by hardware-dev.

## Verified facts (as of 2026-08-12)

**Board**
- ESP32-DevKitC v4, module ESP32-WROOM-32, chip **ESP32-D0WDQ6** rev v1.0, 40MHz crystal.
- USB-serial port on this Mac: `/dev/cu.usbserial-10`. MAC `3c:61:05:2b:c4:a4`.
- Upload note: **921600 baud fails** ("Unable to verify flash chip connection"). Use `UploadSpeed=115200` (`--fqbn esp32:esp32:esp32:UploadSpeed=115200`). Likely the cable/adapter.

**Panels (both 3-color: black / white / red only)**
| Panel | Resolution | GxEPD2 driver class |
|-------|-----------|---------------------|
| 4.2"  | 400 × 300 | `GxEPD2_420c` |
| 7.5"  | 640 × 384 | `GxEPD2_750c` |

**Wiring — identical for both panels, through the seller's small adapter board**
(decoded from the seller's demo sketches; matches `firmware/shared/pins.h`)

| Signal | ESP32 GPIO |
|--------|-----------|
| CS     | 15 |
| DC     | 27 |
| RST    | 26 |
| BUSY   | 25 |
| SCK    | 13 |
| MOSI   | 14 |
| MISO   | not used |

Connection chain (seller's cabling guide `init_resources/huong-dan-cam-cap.jpg`):
`ESP32 board → FFC → adapter board → FFC → e-ink panel`.

**Software stack**
- `arduino-cli` 1.5.1, core `esp32:esp32@3.3.11`, FQBN `esp32:esp32:esp32`.
- Library: seller's modified **GxEPD2 v1.6.1** at `~/Documents/Arduino/libraries/GxEPD2` (+ Adafruit GFX, Adafruit BusIO).
- Build/flash helper: `tools/flash.sh`.

---

## 2026-08-12 — 4.2" panel bring-up: PASS

Flashed `firmware/eink_selftest_4in2` to the 4.2" panel. Serial log:

```
=== E-Ink 4.2" self-test ===
BUSY pin (25) idle level: 0
Panel reports: 400 x 300
Drawing test pattern...
_PowerOn : 70001        (~70 ms)
_Update_Full : 13355001 (~13.3 s full refresh — normal for 3-color)
_PowerOff : 20001
Done. Hibernating.
```

- Panel reports correct 400×300 → `GxEPD2_420c` is the right driver.
- Full refresh completed and powered off cleanly. PO confirmed the 7.5" pattern visually;
  4.2" pattern visual confirm pending (same test-pattern sketch).

## 2026-08-12 — 7.5" panel bring-up: PASS (firmware/electrical + PO visual confirm)

Flashed `firmware/eink_selftest_7in5` to the connected 7.5" panel. Serial log:

```
=== E-Ink 7.5" self-test ===
BUSY pin (25) idle level: 0
Panel reports: 640 x 384
Drawing test pattern...
_PowerOn : 4
_Update_Full : 1
_PowerOff : 1
Done. Hibernating.
```

- Panel reports the correct 640×384 → right driver class.
- BUSY handshake works (init did not hang); full refresh completed and powered off cleanly.
- **Outstanding QA step:** PO must eyeball/photograph the physical panel to confirm the
  test pattern rendered (border, 4 corner squares, black+red bands, diagonal, two text
  lines). Firmware side is confirmed good; panel-defect check is visual.

## TODO
- [ ] Confirm 7.5" test pattern visually (PO photo) → close the QA gate.
- [ ] Bring up the **4.2"** panel (`firmware/eink_selftest_4in2`) — not yet tested.
- [ ] Note BUSY idle polarity per panel if any init instability appears.
