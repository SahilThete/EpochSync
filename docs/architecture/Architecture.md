# EpochSync Architecture

## Overview

EpochSync is a modular PlayStation 2 homebrew project intended to synchronize the console RTC with network time. The repository currently provides the architectural skeleton and initial module implementations rather than a complete end-to-end RTC sync workflow.

The design follows a clear separation of responsibilities so each subsystem can evolve independently.

---

## High-Level Architecture

```text
main.c
  └─ Application
       └─ System
            ├─ Config Manager
            ├─ Network Manager
            ├─ NTP Client
            ├─ RTC Manager
            ├─ Time Manager
            ├─ UI Manager
            └─ Launcher Manager
```

---

## Module Responsibilities

### Application

Responsible for:
- startup and shutdown
- initializing the system layer
- coordinating the main flow

Location:
- [src/core](src/core)

### Config Manager

Responsible for:
- configuration loading and validation
- future persistence and defaults

Location:
- [src/config](src/config)

### Network Manager

Responsible for:
- PS2 network initialization and status handling
- future connection setup and diagnostics

Location:
- [src/network](src/network)

### NTP Client

Responsible for:
- NTP request handling
- response parsing and future time retrieval logic

Location:
- [src/ntp](src/ntp)

### RTC Manager

Responsible for:
- reading and writing RTC values
- future hardware integration and validation

Location:
- [src/rtc](src/rtc)

### Time Manager

Responsible for:
- Unix timestamp to calendar conversions
- RTC conversion logic for the PS2 hardware RTC
- BCD helpers and date validation
- timezone and formatting helpers

Location:
- [src/time](src/time)

### UI Manager

Responsible for:
- future menu and screen rendering flow
- user feedback and prompts

Location:
- [src/ui](src/ui)

### Launcher Manager

Responsible for:
- future launch and exit behavior

Location:
- [src/launcher](src/launcher)

### Common

Shared infrastructure used by the rest of the project:
- logging
- shared types and constants
- module identifiers

Location:
- [src/common](src/common)

---

## Current Initialization Flow

```text
Application Initialize
  ↓
System Initialize
  ↓
Module Startup
  ↓
Application Run / Future Workflow
```

The current application entry point initializes the system layer and then enters the placeholder runtime flow. The full NTP-to-RTC synchronization sequence remains a planned Phase 2+ feature.

---

## Directory Structure

```text
EpochSync/
├── docs/
├── src/
│   ├── common/
│   ├── config/
│   ├── core/
│   ├── launcher/
│   ├── network/
│   ├── ntp/
│   ├── rtc/
│   ├── system/
│   ├── time/
│   └── ui/
├── Makefile
└── README.md
```

---

## Design Principles

- modular architecture
- single responsibility per module
- hardware abstraction where possible
- defensive programming
- clear separation between time math and hardware integration

---

## Target Platform

- PlayStation 2 homebrew
- PS2SDK toolchain

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