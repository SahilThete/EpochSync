# EpochSync PS2 Build Guide

## Prerequisites

- Windows 10/11 (tested)
- Latest precompiled PS2Dev/PS2SDK Windows release downloaded from the ps2dev GitHub releases
- Make for Windows (e.g., from MSYS2 or included with the precompiled release)
- Git
- Standard build tools (gcc, binutils) included in the precompiled package

## Setting Up the Environment

### Method 1: Precompiled Release (Recommended)

1. **Download precompiled release:**
   - Go to https://github.com/ps2dev/ps2dev/releases and download the latest Windows precompiled archive.
   - Extract the archive to a folder, e.g., C:\ps2dev

2. **Configure environment variables (Windows):**
   - Open System Properties -> Environment Variables and add/set:
     - PS2DEV = C:\ps2dev
     - PS2SDK = %PS2DEV%\\ps2sdk
   - Add the toolchain bins to PATH, for example:
     - %PS2DEV%\\bin; %PS2DEV%\\ee\\bin; %PS2DEV%\\iop\\bin; %PS2DEV%\\gsKit\\bin; (add to user PATH)

3. **Optional: Use MSYS2 / MinGW shell**
   - If your Make is from MSYS2, launch the MSYS2 MinGW shell after setting PATH so build tools are available.

### Method 2: Build from Source (Alternative)

For users who prefer to build the PS2Dev toolchain from source:

1. **Clone the PS2Dev repository:**
```bash
git clone https://github.com/ps2dev/ps2dev.git
cd ps2dev
```

2. **Run the build script:**
   - On Windows with MSYS2/MinGW: Execute the provided build script
   - This will compile the entire toolchain locally (may take 30+ minutes)

3. **Set environment variables:**
   - PS2DEV = <path-to-cloned-ps2dev>
   - PS2SDK = %PS2DEV%\\ps2sdk
   - Add to PATH as described in Method 1

**Note:** Building from source requires additional dependencies (gcc, binutils, autotools) and is recommended for developers who need to modify the toolchain.

## Building the Project

### Quick Build

```bash
cd /path/to/EpochSync
make clean
make
```

### Build Steps

1. Clean previous builds:
```bash
make clean
```

2. Compile source code:
```bash
make
```

3. Create ELF executable:
```bash
make elf
```

4. Generate ISO image (optional):
```bash
make iso
```

## Cross-Compiler Targets

This project uses the PS2 cross-compiler targeting:
- EE (Emotion Engine): ee-gcc compiler
- IOP (I/O Processor): iop-gcc compiler

## Troubleshooting

- Compiler not found: Ensure PS2DEV environment variable is set correctly and PATH includes the precompiled bin directories
- Missing dependencies: Verify you downloaded the Windows precompiled release that bundles the SDK and toolchain
- Build errors: Use an MSYS2/MinGW shell if Make or other Unix-like tools are missing

## Build Artifacts

Output files are typically generated in:
- build/ - Compiled object files
- bin/ - Final executables
- *.elf - ELF executable format
