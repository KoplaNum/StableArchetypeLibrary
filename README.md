# StableArchetypeLibrary

StableArchetypeLibrary is a modular C++ neural visual synthesis project for Zorro. It implements a structured 100-equation pipeline for real-time generative rendering, combining:

- **LibTorch** for archetype neural parameter generation
- **OpenCL** for per-pixel neural inference on GPU
- **OpenGL (WGL)** for real-time display with CL/GL shared buffers

## What it does

The system evolves semantic context over time, computes controller/gating weights across archetypes, evaluates archetype neural outputs per pixel, blends the results, and maps them into final RGB output.

Pipeline:

`context -> controller/gating -> archetype outputs -> blending -> final color`

## Main files

- `Mendb11.cpp` - stable baseline implementation
- `Mendb11_patch1_minimal.cpp` - minimal controller variation
- `Mendb11_patch2_archetypes.cpp` - stronger archetype identity shaping
- `Mendb11_patch3_regimes.cpp` - strongest visual-regime and kernel feature variation

## Project structure

- `include/equations/` - equation subsystem headers
- `include/registry/` - registry and equation mapping utilities
- `src/registry/` - subsystem registration and naming support

## Build

See `BUILDING.md` for local setup instructions. Paths are intentionally not hardcoded; configure your environment for:

- Zorro SDK
- LibTorch C++ API
- CUDA Toolkit
- Visual Studio Build Tools (x64)

## Detailed compile guide (Windows)

### 1) Prerequisites

Install and verify:

- Visual Studio 2022 Build Tools (Desktop C++ / MSVC x64)
- CUDA Toolkit
- LibTorch (C++ distribution matching your CUDA version)
- Zorro installation (for `zorro.h` and `ZorroDLL.cpp`)

### 2) Create a local compile script (untracked)

Create a private `.bat` file (outside this repo or git-ignored) and set your machine paths:

```bat
@echo off
setlocal

set "ZORRO_ROOT=REPLACE_WITH_YOUR_ZORRO_PATH"
set "CUDA_ROOT=REPLACE_WITH_YOUR_CUDA_PATH"
set "LIBTORCH_ROOT=REPLACE_WITH_YOUR_LIBTORCH_PATH"
set "VS_AUX_BUILD=REPLACE_WITH_YOUR_VS_AUX_BUILD_PATH"

call "%VS_AUX_BUILD%\vcvars64.bat"
cd /d "%ZORRO_ROOT%"

cl /EHa /fp:strict /Zc:wchar_t /Gd /MD /O2 /std:c++17 /permissive /D "_WINDLL" /D "_MBCS" ^
  /I"%CUDA_ROOT%\include" ^
  /I"%LIBTORCH_ROOT%\include" ^
  /I"%LIBTORCH_ROOT%\include\torch\csrc\api\include" ^
  /I"REPO_PATH\StableArchetypeLibrary\include" ^
  "REPO_PATH\StableArchetypeLibrary\Mendb11.cpp" "%ZORRO_ROOT%\Source\VC++\ZorroDLL.cpp" ^
  /link /DLL /NOLOGO /MACHINE:X64 /OUT:"%ZORRO_ROOT%\Strategy\Mendb1164.dll" ^
  /LIBPATH:"%CUDA_ROOT%\lib\x64" ^
  /LIBPATH:"%LIBTORCH_ROOT%\lib" ^
  OpenGL32.lib OpenCL.lib User32.lib Gdi32.lib ^
  c10.lib c10_cuda.lib torch.lib torch_cpu.lib torch_cuda.lib cudart.lib

endlocal
```

### 3) Compile variants

To build a different visual variant, replace the source file in the command:

- `Mendb11.cpp` (baseline)
- `Mendb11_patch1_minimal.cpp`
- `Mendb11_patch2_archetypes.cpp`
- `Mendb11_patch3_regimes.cpp`

You can also change `/OUT:` to produce separate DLL names, for example:

- `Mendb11_patch1_64.dll`
- `Mendb11_patch2_64.dll`
- `Mendb11_patch3_64.dll`

### 4) Run in Zorro

- Copy/build output DLL into `Zorro\Strategy\`
- Select corresponding strategy script in Zorro
- Press `Train`
- OpenGL window should appear and render in real time

### 5) Common build/runtime issues

- **`torch/... file not found`**: LibTorch include paths are missing or mismatched.
- **Linker cannot find torch/c10 libs**: check `LIBTORCH_ROOT\lib` and `/LIBPATH`.
- **`zorro.h` not found**: verify Zorro include path and `ZorroDLL.cpp` path.
- **OpenGL window not appearing**: ensure correct DLL is loaded in `Zorro\Strategy\` and rebuilt target name matches strategy.

## Notes

- Designed for iterative experimentation with neural visual behavior.
- Baseline and patch variants allow side-by-side comparison without modifying the stable implementation.

## License

This project is licensed under the MIT License. See `LICENSE`.

## Third-Party Legal Notes

This repository depends on third-party SDKs/libraries (Zorro SDK, LibTorch, CUDA, OpenCL/OpenGL, MSVC toolchain) that are licensed separately. See `THIRD_PARTY_NOTICES.md`.

When distributing binaries, ensure you include all required third-party notices/licenses as required by those dependencies.
