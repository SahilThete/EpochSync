# EpochSync Architecture

## Overview

EpochSync is a modular PlayStation 2 utility designed to synchronize the console's Real-Time Clock (RTC) using the Network Time Protocol (NTP).

Unlike the original NTPS2 project, EpochSync is designed around independent modules with clearly defined responsibilities, making future maintenance and feature expansion significantly easier.

---

# High-Level Architecture

```
                 ┌────────────────────┐
                 │      main.c        │
                 │ Application Entry  │
                 └─────────┬──────────┘
                           │
                           ▼
                 ┌────────────────────┐
                 │   Application      │
                 │ Initialization     │
                 └─────────┬──────────┘
                           │
        ┌──────────────────┼──────────────────┐
        ▼                  ▼                  ▼

 Config Manager      Network Manager     UI Manager

        │                  │                  │
        │                  ▼                  │
        │             NTP Client              │
        │                  │                  │
        │                  ▼                  │
        └────────────► RTC Manager ◄──────────┘
                           │
                           ▼
                    Launcher Manager
                           │
                           ▼
                     Exit / Next ELF
```

---

# Module Responsibilities

## Application

Responsible for:

- Program startup
- Initialization sequence
- Main execution loop
- Graceful shutdown

Location

```
src/core/
```

---

## Config Manager

Responsible for:

- Reading INI configuration
- Saving configuration
- Default values
- Validation

Future Features

- Auto Sync
- Selected NTP Server
- Launch Path
- Timezone
- Theme

Location

```
src/config/
```

---

## Network Manager

Responsible for:

- Loading PS2 network modules
- Bringing network online
- DHCP
- Connection status
- Error reporting

Location

```
src/network/
```

---

## NTP Client

Responsible for:

- Sending NTP request
- Receiving response
- Calculating UTC time
- Server failover
- Timeout handling

Future

- Multiple servers
- Automatic best server selection
- Server latency measurements

Location

```
src/ntp/
```

---

## RTC Manager

Responsible for:

- Reading PS2 RTC
- Writing RTC
- Date validation
- Leap year handling

Location

```
src/rtc/
```

---

## UI Manager

Responsible for:

- Rendering interface
- Progress messages
- Menus
- Error dialogs
- Theme support

Future

- Dark Theme
- Classic Theme
- Minimal Theme

Location

```
src/ui/
```

---

## Launcher Manager

Responsible for:

- Returning to uLaunchELF
- Launching OPL
- Launching FMCB apps
- Exit handling

Future

- ELF Browser
- Launch History

Location

```
src/launcher/
```

---

## Common

Shared utilities.

Examples

- Logging
- String helpers
- File helpers
- Error handling

Location

```
src/common/
```

---

# Initialization Flow

```
Application

↓

Load Configuration

↓

Initialize UI

↓

Initialize Network

↓

Request Time

↓

Validate Response

↓

Display Result

↓

User Confirmation (optional)

↓

Write RTC

↓

Launch Next ELF / Exit
```

---

# Directory Structure

```
EpochSync

├── docs/
├── assets/
├── src/
│
├── core/
├── network/
├── ntp/
├── rtc/
├── config/
├── ui/
├── launcher/
├── common/
│
├── Makefile
├── README.md
└── LICENSE
```

---

# Design Principles

- Single Responsibility Principle
- Modular Architecture
- Hardware Abstraction
- Configuration Driven
- Minimal Dynamic Memory
- Defensive Programming
- Backwards Compatible
- Easy to Maintain

---

# Target Platform

Console

PlayStation 2 Slim SCPH-90004

Region

PAL

Framework

PS2SDK

Compiler

GCC 15.2.0

Graphics

gsKit

Network

PS2SDK Network Stack

RTC

PS2SDK RTC API