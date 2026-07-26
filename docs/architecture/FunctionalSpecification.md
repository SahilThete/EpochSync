# EpochSync Functional Specification

Version: 0.2 Draft

Project Status:
Early scaffold / pre-alpha

Target Platform:
Sony PlayStation 2 homebrew

Framework:
PS2SDK

Compiler:
PS2 cross-compiler toolchain (GCC-based)

---

# 1. Introduction

## 1.1 Purpose

EpochSync is a modular PlayStation 2 utility project intended to synchronize the console RTC using network time. The current repository focuses on establishing the module architecture and shared helper layers for future RTC synchronization work.

The project emphasizes:

- modular design
- maintainability
- separation between time math and hardware integration
- future extensibility

---

## 1.2 Objectives

EpochSync shall eventually:

- synchronize the PS2 RTC with network time
- validate received or computed time before writing
- provide user feedback during synchronization
- optionally request user confirmation
- optionally launch another ELF after synchronization
- remain compatible with PS2SDK-based homebrew environments

At the current stage, the codebase implements the foundation and time-management layer, while the full synchronization workflow remains planned.

---

# 2. Supported Platforms

Current Target

- PlayStation 2 homebrew environment
- PS2SDK-based builds

Planned / Future

- PlayStation 2 hardware
- PCSX2
- additional homebrew toolchain setups

---

# 3. Functional Requirements

## FR-001

Application Startup

Description

The application shall initialize the required system and module layers.

Current Status

Implemented at the scaffold level.

---

## FR-002

Configuration Management

Description

Configuration handling shall load and validate settings when implemented.

Current Status

Module skeleton exists; full runtime behavior is pending.

---

## FR-003

Time Management

Description

The application shall support calendar conversion, leap-year validation, RTC conversion, timezone handling, and time formatting.

Current Status

Implemented in the TimeManager module.

---

## FR-004

RTC Integration

Description

The project shall provide RTC read/write support using PS2 hardware integration.

Current Status

Module scaffold exists; actual hardware calls are still pending.

---

## FR-005

NTP Integration

Description

The project shall eventually retrieve and validate network time.

Current Status

Client and network module skeletons exist; full implementation is pending.

---

## FR-006

Launcher Integration

Description

The project shall support launching another ELF or exiting after synchronization.

Current Status

Launcher module scaffold exists; behavior is not yet implemented.

---

# 4. Non-Functional Requirements

## Maintainability

Modules shall remain independent and follow a clear responsibility boundary.

## Portability

Code should remain compatible with the PS2SDK build environment and be straightforward to extend.

## Reliability

The implementation should validate input and avoid invalid date or RTC conversions.

---

# 5. Current Implementation Notes

The current codebase includes:

- application startup scaffold
- system initialization layer
- shared logging and constants
- configuration, network, NTP, RTC, launcher, and UI module stubs
- a working TimeManager implementation for conversion and formatting helpers

The full user-facing synchronization workflow is still planned for future development.

Load Config

↓

Initialize Network

↓

Request Time

↓

Write RTC

↓

Launch Next ELF
```

---

# 7. Error Handling

Network Failure

Display

```
Unable to initialize network.
```

---

DNS Failure

Display

```
Unable to resolve NTP server.
```

---

Timeout

Display

```
Server timeout.
Retrying...
```

---

RTC Failure

Display

```
Unable to update RTC.
```

---

Launch Failure

Display

```
Unable to launch application.
```

---

# 8. Supported NTP Servers

Default

```
pool.ntp.org
```

Additional

```
time.cloudflare.com

time.google.com

time.windows.com

time.nist.gov
```

---

# 9. Compatibility

Compatible With

✓ FMCB

✓ OPL

✓ uLaunchELF

✓ PS2SDK

Future

✓ Open PS2 Loader

✓ PCSX2

---

# 10. Logging

Development builds may enable logging.

Release builds shall disable debug logging by default.

Future log levels

- Error
- Warning
- Info
- Debug

---

# 11. Exit Behaviour

User selectable.

Supported modes

- Exit
- Return to Browser
- Return to uLaunchELF
- Launch configured ELF

---

# 12. User Interface Requirements

The interface shall:

- remain readable on CRT and LCD televisions
- support PAL safe area
- avoid unnecessary animations
- remain responsive
- use controller navigation only

---

# 13. Future Features

Planned

- Theme support
- Localization
- Clock drift estimation
- Automatic timezone
- DST support
- Network diagnostics
- Update checker
- Plugin architecture

---

# 14. Acceptance Criteria

EpochSync shall be considered Version 1.0 ready when:

✓ RTC synchronization succeeds reliably.

✓ Multiple NTP servers are supported.

✓ Configuration system is stable.

✓ Auto-launch functions correctly.

✓ Error handling covers all expected failures.

✓ Compatible with FMCB.

✓ Compatible with OPL.

✓ Compatible with uLaunchELF.

✓ Documentation complete.

✓ Codebase fully modular.

✓ Successfully tested on SCPH-90004 PAL hardware.

---

# 15. Out of Scope

EpochSync will NOT:

- replace the PS2 Browser
- continuously synchronize time in the background
- modify BIOS settings
- require internet beyond NTP
- collect or transmit user information
- modify FMCB or OPL
- install system files

---

# 16. Guiding Principles

The project prioritizes:

1. Reliability over feature count.

2. Predictable behaviour.

3. Clean modular architecture.

4. Easy maintenance.

5. Backward compatibility.

6. Minimal user interaction for common workflows.

7. Full transparency of application behaviour.