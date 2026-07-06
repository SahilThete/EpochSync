# VS Code Setup Guide

This document describes the recommended Visual Studio Code configuration for working on the PS2 development environment in this repository.

## 1. Install VS Code

- Download and install Visual Studio Code from https://code.visualstudio.com/
- Launch VS Code after installation.

## 2. Recommended Extensions

Install the following extensions to improve PS2 development productivity:

- `ms-vscode.cpptools` - C/C++ IntelliSense, debugging, and code browsing
- `ms-vscode.cmake-tools` - CMake integration and build management (if this repo uses CMake)
- `eamodio.gitlens` - Git history and inline blame support
- `ms-vscode-remote.remote-ssh` - Remote development if working on a remote build environment

## 3. Open the Repository

- Open the repository folder in VS Code: `File -> Open Folder...`
- Select the root folder of the project.

## 4. PS2 Workspace Settings

Create or update `.vscode/settings.json` in the repository if needed. Sample settings for PS2 toolchain integration:

```json
{
  "files.exclude": {
    "**/build": true,
    "**/.vscode": false
  },
  "editor.formatOnSave": true,
  "editor.tabSize": 2,
  "editor.detectIndentation": false,
  "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
  "C_Cpp.default.includePath": [
    "${workspaceFolder}/include",
    "${workspaceFolder}/ps2sdk/include",
    "${workspaceFolder}/ps2sdk/ee/include",
    "${workspaceFolder}/ps2sdk/iop/include"
  ],
  "C_Cpp.default.compilerPath": "C:/ps2dev/bin/ee-gcc.exe"
}
```

Adjust `compilerPath` and include paths for your local PS2DEV/PS2SDK installation.

## 5. Configure Build and Debug

### Build

Use the PS2 build system configured for this repo. Example `tasks.json` for a standard PS2 make-based build:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "build",
      "type": "shell",
      "command": "make",
      "args": ["all"],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": ["$gcc"]
    }
  ]
}
```

If the repo uses CMake, replace the command with `cmake --build build` and configure the build folder accordingly.

### Debug

For PS2 development, debugging typically uses an emulator or remote stub such as PCSX2 with GDB support. Example `.vscode/launch.json` configuration for attaching to a PS2 debug stub:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Attach to PS2 emulator",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/your-executable.elf",
      "args": [],
      "cwd": "${workspaceFolder}",
      "MIMode": "gdb",
      "miDebuggerPath": "C:/ps2dev/bin/r3000-elf-gdb.exe",
      "miDebuggerServerAddress": "localhost:1234",
      "preLaunchTask": "build",
      "setupCommands": [
        {
          "description": "Connect to PS2 GDB stub",
          "text": "target remote localhost:1234"
        }
      ]
    }
  ]
}
```

Update `program`, `miDebuggerPath`, and server address to match your emulator or hardware debug setup.

## 6. Working with Source Control

- Use the Source Control view to commit and push changes.
- Use GitLens or built-in Git features to review history and diffs.

## 7. Tips

- Use the integrated terminal: `View -> Terminal`.
- Run `make`, `cmake`, or PS2 toolchain commands from the terminal if needed.
- Keep workspace settings minimal and avoid committing personal settings unless they benefit the entire team.
