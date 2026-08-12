---
description: Design Ideation for an e-ink screen — generate HTML mockups at real panel pixel size (B/W/R only) for the PO to approve before firmware-dev renders them.
---

# /design — E-Ink screen mockups

Produce HTML mockups of an e-ink screen so the PO can approve a layout **before** any
firmware is written. Driven by ux-designer (via Coordinator).

## Rules
- **Canvas = real panel pixels, 1:1.** 4.2" → 400×300, 7.5" → 640×384. A fixed-size
  `div` at exactly those pixels with a 1px border = the panel bezel. Do NOT use a phone frame.
- **Colors: black, white, red only.** No gray, no gradients, no shadows, no anti-aliased
  color. Use `#000`, `#fff`, and one red (`#d00`). Solid fills and hairlines only — this
  is what the panel can actually show.
- **Large, high-contrast type.** E-ink is read at arm's length. Reserve red for one or
  two emphasis elements.
- Put **3 variants side by side** in one standalone HTML file, each labeled, each at true
  panel size. Vietnamese placeholder content that matches the real use-case.
- Save to `docs/03-codebase/design/html-mockups/<screen>-variants.html`. Archive previous
  versions to `html-mockups/archive/` with a `-v1/-v2` suffix.
- After the PO picks one, ux-designer writes the pixel-exact design spec to
  `docs/03-codebase/design/specs/<key>.md` for firmware-dev.

## Usage
`/design <screen> cho màn <4.2|7.5>` — e.g. `/design màn đồng hồ + thời tiết cho màn 7.5`
