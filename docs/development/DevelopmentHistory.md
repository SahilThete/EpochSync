# Development History

## 2026-07-06

### PS2DEV Environment

Problem

Official PS2DEV Windows release could not start GCC.

Error

0xc000007b

Root Cause

Official PS2DEV ships a 32-bit GCC executable.

64-bit UCRT DLLs were mistakenly used.

Solution

Installed required MSYS2 MINGW32 runtime packages:

- libiconv
- libwinpthread
- gmp
- mpfr
- isl
- mpc
- zstd

Result

GCC 15.2.0 fully operational.