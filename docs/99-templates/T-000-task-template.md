---
id: T-000
title: <short title>
assignee: <firmware-dev | hardware-dev | backend-dev | ba | ux-designer | pm | qa>
status: TODO         # TODO | IN_PROGRESS | BLOCKED | REVIEW | DONE
phase: phase-01-bring-up
wave: wave-1
priority: P1         # P0 | P1 | P2
scope: [firmware]    # firmware | hardware | backend | both
panel: 7.5           # 4.2 | 7.5 | n/a
design_required: no  # yes -> ux-designer produces a mockup first
design_ref: <path or n/a>
spec_ref: <docs/01-specs/features/<key>/spec.md or n/a>
dependencies: []
---

## Goal
<what user outcome this delivers, one paragraph>

## Scope
- In: <...>
- Out: <...>

## Clarifying questions (≥3, then STOP and WAIT)
1.
2.
3.

### Answers from PO
| # | Answer |
|---|--------|

## Acceptance criteria
- [ ] <testable, mappable to a qa check>

## QA evidence (filled by qa)
- Build: <arduino-cli compile result>
- Serial log: <paste / path>
- Panel photo: <path — REQUIRED for firmware/hardware tasks; no photo = not done>
- Verdict: <PASS | FAIL + deviation>

## Output contract (when done)
- Sketch/service path, branch, suggested commit message.
- `git show --stat HEAD` output if committed.
