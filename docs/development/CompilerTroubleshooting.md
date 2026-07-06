# Compiler Troubleshooting Guide

This document explains how to diagnose and repair the EpochSync Windows development environment.

Use a regular Command Prompt or PowerShell session with the PS2DEV environment configured.

---

# 1. Verify GCC

Run:

```cmd
mips64r5900el-ps2-elf-gcc --version
```

Expected:

```
mips64r5900el-ps2-elf-gcc (GCC) 15.2.0
```

---

# 2. Verify Compiler Include Paths

Run:

```cmd
mips64r5900el-ps2-elf-gcc -xc -E -v NUL
```

Expected:

```
#include <...> search starts here:
...
End of search list.
```

---

# 3. Verify Compiler Include Directory

Run:

```cmd
mips64r5900el-ps2-elf-gcc -print-file-name=include
```

Expected:

```
...\ee\lib\gcc\mips64r5900el-ps2-elf\15.2.0\include
```

---

# 4. Verify Compiler Search Directories

Run:

```cmd
mips64r5900el-ps2-elf-gcc -print-search-dirs
```

Verify all directories point to the local PS2DEV installation.

---

# 5. Verify Environment Variables

Run:

```cmd
echo %PS2DEV%
echo %PS2SDK%
```

Expected:

```
E:\Projects\PS2Dev\ps2dev
E:\Projects\PS2Dev\ps2dev\ps2sdk
```

---

# 6. Verify IntelliSense

Open

View → Output → C/C++

Run

```
C/C++: Log Diagnostics
```

Verify:

- compilerPath
- include paths
- GCC include directories

---

# 7. Reset IntelliSense Cache

Delete

```
C:\Users\<User>\AppData\Local\Microsoft\vscode-cpptools
```

Restart VS Code.

---

# Common Problems

## 0xc000007b

### Cause

Mixed 32-bit and 64-bit DLLs.

### Fix

Use the 32-bit MSYS2 MINGW32 runtime DLLs.

Never mix them with UCRT64 DLLs.

---

## Missing DLL

### Cause

Required runtime package not installed.

### Fix

Install the corresponding package with pacman.

---

## stdbool.h not found

### Cause

IntelliSense is not using the PS2 compiler.

### Fix

Verify:

- compilerPath
- include paths
- IntelliSense cache

---

## Compiler cannot start

### Check

```
gcc --version
```

If this fails:

- PATH
- Runtime DLLs
- Environment variables

must be checked first.

---

## Diagnostic Order

Always troubleshoot in this order:

1. gcc --version

↓

2. gcc -xc -E -v NUL

↓

3. gcc -print-file-name=include

↓

4. gcc -print-search-dirs

↓

5. echo %PS2DEV%

↓

6. echo %PS2SDK%

↓

7. C/C++: Log Diagnostics