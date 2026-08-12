# Spec: <feature name>

- key: <feature-key>
- owner: ba
- status: draft | approved
- design_required: yes | no

## Goal
<user outcome, one paragraph>

## Scope
- In:
- Out:

## Display behavior
- What appears on the panel: <...>
- Refresh strategy: full (clears ghosting, flickers ~2–20s) | partial (fast, may ghost) — and how often.
- On power loss: e-ink keeps its last image — describe intended resting state.

## Data
- Source: on-device | WiFi/HTTP | backend service
- Update frequency: <...>
- Offline / failure behavior: <...>

## Constraints
- Colors: black / white / red only.
- Panel: <4.2 400×300 | 7.5 640×384>.
- Power budget: <deep-sleep between refreshes? battery/USB?>

## Acceptance criteria
- AC-1:
- AC-2:

## Test scenarios (qa runs on real board)
- TS-1:
- TS-2:

## Open questions / spikes needed
- <e.g. 3rd-party API limits — research spike before implementation>
