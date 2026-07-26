# EpochSync Development Roadmap

This roadmap tracks the current development direction for EpochSync as an early-stage PS2 homebrew project.

---

# Current Status

Version

```text
Pre-Alpha
```

Project State

```text
Architecture scaffold and module foundation
```

---

# Phase 0

## Project Foundation

Status

✅ Complete

Tasks

- repository layout established
- source module skeletons created
- documentation added
- PS2SDK build configuration wired up

---

# Phase 1

## Core Module Foundation

Status

🚧 In Progress

Tasks

- application startup and shutdown flow
- shared logging and constants
- config/network/NTP/RTC/launcher/UI module placeholders
- TimeManager implementation for conversion and formatting

Goal

Establish a maintainable, modular codebase for future RTC synchronization work.

---

# Phase 2

## Runtime Workflow

Status

⬜ Planned

Features

- end-to-end NTP retrieval flow
- RTC update workflow
- user confirmation and error handling
- launcher integration

---

# Phase 3

## Configuration and UX

Status

⬜ Planned

Features

- persistent INI-based configuration
- user-facing menus and messages
- richer status and error feedback

---

# Phase 4

## Advanced Time Handling

Status

⬜ Planned

Features

- timezone-aware display handling
- DST support
- broader RTC validation and diagnostics

---

# Phase 5

## Polish and Release

Status

⬜ Planned

Features

- testing on real PS2 hardware
- packaging and release workflow
- final documentation and user guide


## v0.4

Multiple NTP servers

---

## v0.5

Launcher improvements

---

## v0.6

Network diagnostics

---

## v0.7

Localization

---

## v0.8

Performance optimization

---

## v0.9

Release Candidate

---

## v1.0

Stable Public Release

Goals

✓ Professional UI

✓ Modular Architecture

✓ Multiple Servers

✓ Configurable Behaviour

✓ Auto Launch

✓ Robust Error Handling

✓ Comprehensive Documentation

✓ Reliable RTC Synchronization

✓ Suitable as the definitive PS2 NTP utility