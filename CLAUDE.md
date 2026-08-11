# E-Ink Project — Team & Workflow (source of truth)

This repo builds and ships a **touch e-ink display product** on ESP32. Right now we
are in **bring-up**: prove the seller's kit + panels work, then grow toward a real
product (content on the panel, driven over WiFi/USB, in a 3D-printed enclosure).

This file is the single source of truth for how the AI team works. It follows the
same model as the PO's other teams (`miwiz-mobile`, `bap-bean-book`, `ta-studio-ops`):
one **Coordinator** talks to the PO, specialized sub-agents do the work, and an
**Architect** gates merges. Hardware here plays the role that "mobile screenshots"
play there — nothing is DONE until it has run on the real board and the panel was
photographed.

---

## 1. The team (`.claude/agents/`)

| Agent | model | color | Owns | One-line role |
|-------|-------|-------|------|---------------|
| **coordinator** | sonnet | green | session, waves | ONLY agent that talks to the PO; plans, delegates, signs off on evidence |
| **pm** | sonnet | purple | product ideas | Use-cases for the e-ink product, Feature Briefs, goal validation |
| **ba** | sonnet | blue | `docs/01-specs/` | Writes specs — the source of truth for what to build |
| **ux-designer** | sonnet | purple | `docs/03-codebase/design/` | Screen layouts within e-ink limits (mono / B-W-R, no partial color), `/design` mockups |
| **firmware-dev** | sonnet | yellow | `firmware/` | ESP32 Arduino/C++, GxEPD2 driver, rendering, WiFi, power |
| **hardware-dev** | sonnet | orange | `docs/hardware/` | Wiring, panel bring-up, FFC/adapter, power, 3D enclosure, defect diagnosis |
| **backend-dev** | sonnet | cyan | `services/` | Content/provisioning service that pushes what the panel shows (added when needed) |
| **qa** | sonnet | cyan | `firmware/**/tests`, QA gate | Flash-to-real-board + photograph-the-panel gate; reproduce-first for bugs |
| **architect** | **opus** | red | `docs/02-architecture/` | REVIEW ONLY — PASS/FAIL/BLOCKED gate, ADRs, does not write product code |

Separation of duties (non-negotiable): the agent who **implements**, the agent who
**verifies** (qa), and the agent who **orchestrates** (coordinator) are three
different roles. The Coordinator signs off on artifacts (serial logs + panel
photos), it does not "eyeball" hardware itself.

## 2. The workflow

```
IDEA (pm) → SPEC (ba) → DESIGN (ux-designer, if design_required) →
IMPLEMENT (firmware-dev / hardware-dev / backend-dev) →
QA GATE (qa: build + flash + photograph panel + read serial) →
REVIEW (architect: PASS / FAIL / BLOCKED) → MERGE (PO only)
```

Rules:
- **No spec = no code.** Bring-up throwaways are the one exception and must be tagged `lab-*`.
- **Bug = reproduce first.** Never fix a bug before reproducing it (a failing test, or a documented flash-and-observe repro).
- **Hardware evidence is mandatory.** A firmware task is not DONE until qa has flashed it to the real ESP32 and attached: (a) the serial log, (b) a photo of the panel. No photo = not done.
- **The PO is the only person who merges to `main`.** Agents work on branches and propose commit messages + PR bodies.

## 3. Session protocol

- **`SESSION START`** — Coordinator reads `docs/04-phases/claude-active-phase.md`, the active phase's `session-log.md` and `task-board.md`, reports what changed, proposes 3 next actions, then WAITS for the PO.
- **`SESSION END`** — Coordinator drafts a State-of-the-Union entry (≤60 lines) into the active phase `session-log.md` for the PO to review.

## 4. Language & communication

- Coordinator ↔ PO: **Vietnamese**, plain and non-jargony. Translate hardware terms (SPI, BUSY, FFC, waveform, ghosting) into everyday language, with an "Đề xuất của em" (my recommendation) block.
- Code, commits, docs, agent-to-agent: **English**.
- PR descriptions / test guides for the PO: **Vietnamese**.

## 5. Hardware facts (verified 2026-08-12)

- **Board:** ESP32-DevKitC v4, module ESP32-WROOM-32, chip ESP32-D0WDQ6. Serial: `/dev/cu.usbserial-10`.
- **Panels:** 4.2" 3-color (400×300, `GxEPD2_420c`) and 7.5" 3-color (640×384, `GxEPD2_750c`). B/W/R only.
- **Wiring (same for both panels, via seller's adapter board):**
  CS=15, DC=27, RST=26, BUSY=25, SCK=13, MOSI=14, MISO=unused.
- **Library:** seller's modified `GxEPD2` (v1.6.1) installed to `~/Documents/Arduino/libraries/GxEPD2`; depends on Adafruit GFX.
- **Toolchain:** `arduino-cli` (FQBN `esp32:esp32:esp32`) + `esptool`. Build/flash via `tools/flash.sh`.
- The 7.5" panel was already seen working (photo `init_resources/IMG_4257`). The 4.2" is not yet confirmed.

See `docs/hardware/bring-up.md` for details and `firmware/shared/pins.h` for the pin map.

## 6. Repo layout

```
firmware/          ESP32 sketches (one folder per sketch) + shared/
services/          content/provisioning backend (added when needed)
tools/             flash.sh and other dev scripts
docs/
  00-research/     product & hardware research
  01-specs/        BA-owned feature specs  (features/<key>/)
  02-architecture/ ADRs, gates
  03-codebase/     design/ (tokens, mockups, layouts), firmware notes
  04-phases/       phase-NN-* / { task-board.md, session-log.md, wave-N/T-XXX.md } + claude-active-phase.md
  99-templates/    task, session-log, ADR, design-spec, spec templates
  hardware/        wiring, bring-up log, panel datasheets, enclosure notes
init_resources/    seller-provided originals (do not edit)
```
