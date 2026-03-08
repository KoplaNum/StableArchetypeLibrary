# Build Instructions (Local Setup Required)

This project depends on:
- Zorro SDK headers/libraries
- LibTorch (C++ API)
- CUDA Toolkit
- Visual Studio Build Tools (MSVC x64)

No machine-specific absolute paths are required in source files.

## Windows compile template

Create a local `.bat` file outside this repository (or keep it untracked) and set these variables:

```bat
set ZORRO_ROOT=REPLACE_WITH_YOUR_ZORRO_PATH
set CUDA_ROOT=REPLACE_WITH_YOUR_CUDA_PATH
set LIBTORCH_ROOT=REPLACE_WITH_YOUR_LIBTORCH_PATH
set VS_AUX_BUILD=REPLACE_WITH_YOUR_VCVARS_PATH
```

Then call `vcvars64.bat`, compile the selected `Mendb11*.cpp`, and link against:

- `OpenGL32.lib`, `OpenCL.lib`, `User32.lib`, `Gdi32.lib`
- `c10.lib`, `c10_cuda.lib`, `torch.lib`, `torch_cpu.lib`, `torch_cuda.lib`, `cudart.lib`

## Notes

- Keep local paths in untracked/private scripts.
- Do not commit credentials, machine-specific paths, or private build automation.
