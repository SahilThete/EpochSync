# EpochSync Functional Specification

Version: 0.1 Draft

Project Status:
Pre-Alpha

Target Platform:
Sony PlayStation 2

Supported Hardware:
PlayStation 2 Slim SCPH-90004 (PAL)

Framework:
PS2SDK

Compiler:
GCC 15.2.0

---

# 1. Introduction

## 1.1 Purpose

EpochSync is a standalone PlayStation 2 utility designed to synchronize the console's Real-Time Clock (RTC) using the Network Time Protocol (NTP).

The project is a complete architectural rewrite inspired by NTPS2 with emphasis on:

- modular design
- improved reliability
- improved user experience
- maintainability
- future extensibility

---

## 1.2 Objectives

EpochSync shall:

- synchronize the PS2 RTC with an NTP server
- validate received time before writing
- provide user feedback during synchronization
- optionally request user confirmation
- optionally launch another ELF after synchronization
- maintain compatibility with existing PS2 homebrew environments

---

# 2. Supported Platforms

Current Target

- PlayStation 2 Slim SCPH-90004
- PAL Region

Planned Support

- All PS2 Slim models
- FAT models
- PCSX2

---

# 3. Functional Requirements

## FR-001

Application Startup

Description

Application shall initialize all required PS2 subsystems.

Success Criteria

Application reaches main menu without crash.

---

## FR-002

Configuration Loading

Description

Application shall load configuration from an INI file.

If configuration is missing:

- defaults shall be used
- application shall continue

---

## FR-003

Network Initialization

Description

Application shall initialize the PS2 network stack.

Success Criteria

Network ready.

Failure

Display appropriate error.

---

## FR-004

NTP Synchronization

Description

Application shall send an NTP request.

Receive response.

Calculate UTC.

Validate response.

---

## FR-005

RTC Update

Description

Application shall convert NTP timestamp into PS2 RTC format.

User confirmation may be requested.

RTC shall then be updated.

---

## FR-006

User Confirmation

Description

Configuration determines behaviour.

Manual Mode

Ask user before writing RTC.

Automatic Mode

Write immediately.

---

## FR-007

Launcher

Description

Depending on configuration:

- Exit
- Return to uLaunchELF
- Launch configured ELF

---

## FR-008

Configuration Saving

Description

Changes made by user shall persist.

---

## FR-009

Server Selection

Description

User may select:

- Automatic
- Manual

Manual selection shall display available servers.

---

## FR-010

Server Failover

Description

If server fails:

Attempt next server.

Maximum retries configurable.

---

## FR-011

Error Reporting

Application shall display meaningful errors.

No silent failures.

---

# 4. Non-Functional Requirements

## Performance

Application startup

< 2 seconds

NTP timeout

Default

5 seconds

Maximum

15 seconds

---

## Memory

Dynamic allocation shall be minimized.

Memory leaks are unacceptable.

---

## Stability

Unexpected crashes are unacceptable.

Configuration corruption shall not occur.

---

## Maintainability

Modules shall remain independent.

Single Responsibility Principle shall be followed.

---

## Portability

Code should compile on future PS2SDK releases with minimal changes.

---

# 5. Configuration

Configuration file

```
EpochSync.ini
```

Example

```
AutoSync=true

ConfirmRTC=false

PreferredServer=pool.ntp.org

ServerMode=Automatic

AutoLaunch=true

LaunchPath=mc0:/BOOT/OPNPS2LD.ELF

Theme=Dark

Timeout=5000

RetryCount=3
```

---

# 6. User Workflow

Manual Mode

```
Launch

↓

Load Config

↓

Initialize Network

↓

Request Time

↓

Display Retrieved Time

↓

Confirm

↓

Write RTC

↓

Launch Next ELF / Exit
```

Automatic Mode

```
Launch

↓

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