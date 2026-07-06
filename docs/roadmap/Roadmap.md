# EpochSync Development Roadmap

This roadmap tracks the planned development of EpochSync from the initial rewrite to the first stable public release.

---

# Current Status

Version

```
Pre-Alpha
```

Project State

```
Architecture Phase
```

---

# Phase 0

## Project Foundation

Status

✅ Complete

Tasks

- Repository created
- Directory layout
- Documentation
- Build Environment
- VS Code Configuration
- PS2DEV Setup

---

# Phase 1

## Core Rewrite

Status

🚧 In Progress

Tasks

- Application Framework
- Logger
- Config Manager
- RTC Manager
- Network Manager
- NTP Client
- Launcher Manager

Goal

Feature parity with NTPS2.

---

# Phase 2

## Modern UI

Status

⬜ Planned

Features

- New Interface
- Better Typography
- Progress Screens
- Status Messages
- Error Dialogs
- Controller Navigation
- Theme Engine

---

# Phase 3

## Configuration System

Status

⬜ Planned

Features

INI Support

Example

```
AutoSync=true
AutoLaunch=true
LaunchPath=mc0:/BOOT/OPNPS2LD.ELF

ConfirmRTC=false

PreferredServer=pool.ntp.org

Theme=Dark
```

---

# Phase 4

## Network Improvements

Status

⬜ Planned

Features

- Server List
- Automatic Failover
- DNS Validation
- Timeout Retry
- Better Errors

Servers

- pool.ntp.org
- time.google.com
- time.cloudflare.com
- time.windows.com

---

# Phase 5

## Launcher Improvements

Status

⬜ Planned

Features

- Auto Launch
- ELF Browser
- Recent Applications
- Return to Previous App

---

# Phase 6

## Advanced Features

Status

⬜ Planned

Features

- Automatic Timezone
- DST Support
- Region Detection
- Network Diagnostics
- Clock Drift Detection

---

# Phase 7

## Polish

Status

⬜ Planned

Features

- Localization
- Icon Pack
- Sound Effects
- Animation
- Settings Menu

---

# Phase 8

## Testing

Status

⬜ Planned

Testing Platforms

- SCPH-90004 PAL
- OPL
- FMCB
- uLaunchELF
- PCSX2

---

# Phase 9

## Release Candidate

Status

⬜ Planned

Requirements

- Stable
- No Memory Leaks
- Documentation Complete
- User Guide
- Changelog
- GitHub Releases

---

# Version History

## v0.1

Goal

Feature parity with NTPS2

---

## v0.2

Configuration system

---

## v0.3

Modern UI

---

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