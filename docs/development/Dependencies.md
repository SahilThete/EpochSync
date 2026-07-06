# Dependencies

## MSYS2 MINGW32 Runtime Packages

mingw-w64-i686-libiconv
mingw-w64-i686-libwinpthread
mingw-w64-i686-gmp
mingw-w64-i686-mpfr
mingw-w64-i686-isl
mingw-w64-i686-mpc
mingw-w64-i686-zstd

## Installation Guide

### Prerequisites
- MSYS2 installed on your system
- Administrator access

### Installation Steps

1. **Open MSYS2 MinGW 32-bit terminal**
   - Launch the MSYS2 application and select the MINGW32 environment

2. **Update package manager**
   ```bash
   pacman -Syu
   ```

3. **Install all dependencies**
   ```bash
   pacman -S mingw-w64-i686-libiconv mingw-w64-i686-libwinpthread mingw-w64-i686-gmp mingw-w64-i686-mpfr mingw-w64-i686-isl mingw-w64-i686-mpc mingw-w64-i686-zstd
   ```

   Or install individually:
   ```bash
   pacman -S mingw-w64-i686-libiconv
   pacman -S mingw-w64-i686-libwinpthread
   pacman -S mingw-w64-i686-gmp
   pacman -S mingw-w64-i686-mpfr
   pacman -S mingw-w64-i686-isl
   pacman -S mingw-w64-i686-mpc
   pacman -S mingw-w64-i686-zstd
   ```

4. **Verify installation**
   ```bash
   pacman -Qs mingw-w64-i686
   ```

## PATH Configuration

The MSYS2 MINGW32 binaries are typically located at:
```
C:\msys64\mingw32\bin
```

This directory should be automatically added to your PATH when using the MINGW32 terminal. If needed, manually add it to your system PATH environment variable.


## Tested Development Environment

| Component | Version |
|-----------|---------|
| Windows | Windows 10 Home 22H2 |
| VS Code | Latest |
| PS2DEV | v2.0.0 Official Windows Release |
| GCC | 15.2.0 |
| MSYS2 | MINGW32 |
| Target Console | PS2 Slim SCPH-90004 (PAL) |

## Environment Variables

Create the following Windows environment variables.

PS2DEV
E:\Projects\PS2Dev\ps2dev

PS2SDK
E:\Projects\PS2Dev\ps2dev\ps2sdk

## Runtime Architecture

The official PS2DEV Windows v2.0.0 release uses a 32-bit GCC executable.

Therefore:

✓ Use MSYS2 MINGW32 runtime libraries.

Do NOT use:

✗ UCRT64
✗ MINGW64
✗ CLANG64

Mixing 64-bit runtime DLLs with the supplied compiler causes Windows error:

0xc000007b