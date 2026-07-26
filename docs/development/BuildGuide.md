# EpochSync PS2 Build Guide

## Prerequisites

- Windows 10/11 or a compatible Unix-like shell
- a PS2SDK/PS2DEV toolchain installation
- GNU make
- Git

## Environment Setup

Set the following environment variables before building:

```bash
export PS2DEV=/path/to/ps2dev
export PS2SDK=$PS2DEV/ps2sdk
export PATH=$PS2DEV/bin:$PS2DEV/ee/bin:$PS2DEV/iop/bin:$PS2DEV/gsKit/bin:$PATH
```

On Windows, use the equivalent environment variable syntax in PowerShell or CMD.

## Building the Project

From the repository root:

```bash
make clean
make
```

This produces an ELF binary named EpochSync.elf.

## Available Targets

- make — build the project
- make clean — remove build artifacts
- make rebuild — clean and rebuild
- make debug — build with debug flags
- make release — build a release image and strip the binary
- make size — show binary size
- make info — inspect ELF headers
- make sections — inspect sections
- make symbols — list symbols
- make disasm — disassemble the binary

## Notes

The current Makefile builds the full source tree under [src](src), including the new [src/time](src/time) module. The repository does not currently define a dedicated ISO or binary packaging target beyond the ELF output.

## Troubleshooting

- missing compiler: verify PS2DEV and PS2SDK are set correctly
- build errors: confirm the toolchain binaries are available on PATH
- stale artifacts: run make clean before rebuilding after major changes
