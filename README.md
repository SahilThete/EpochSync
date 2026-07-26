# EpochSync

EpochSync is a PlayStation 2 homebrew project for building a modular RTC synchronization utility around the PS2SDK toolchain.

## Project Status

The repository currently contains the initial project scaffold and a set of modular source files for application startup, logging, configuration, network, RTC, launcher, UI, and time handling. The core workflow is still in an early implementation phase, and many subsystems are placeholders for later Phase 2 work.

## Repository Layout

- [src](src) — application entry point and module implementations
  - [src/core](src/core) — application coordinator
  - [src/common](src/common) — shared types, constants, and logger
  - [src/config](src/config) — configuration management
  - [src/network](src/network) — network manager
  - [src/ntp](src/ntp) — NTP client
  - [src/rtc](src/rtc) — RTC manager
  - [src/system](src/system) — PS2 system initialization
  - [src/time](src/time) — time conversion and formatting helpers
  - [src/ui](src/ui) — UI manager
  - [src/launcher](src/launcher) — launcher manager
- [docs](docs) — architecture, roadmap, and development notes
- [Makefile](Makefile) — PS2 build configuration

## Build

This project is built with the PS2SDK toolchain.

```bash
make clean
make
```

## Documentation

- [docs/architecture/Architecture.md](docs/architecture/Architecture.md)
- [docs/architecture/FunctionalSpecification.md](docs/architecture/FunctionalSpecification.md)
- [docs/development/BuildGuide.md](docs/development/BuildGuide.md)
- [docs/roadmap/Roadmap.md](docs/roadmap/Roadmap.md)

## Notes

The current implementation focuses on structure, modular boundaries, and the shared time-management layer. Full RTC synchronization and UI flows are still planned for later development stages.
