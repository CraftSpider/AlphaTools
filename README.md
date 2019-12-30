# AlphaTools
[![Build status](https://ci.appveyor.com/api/projects/status/27kyci6ra7iq6h1k?svg=true)](https://ci.appveyor.com/project/CraftSpider/alphatools)

C++ utilities for GCD and other things

## Usage

### Requirements

- Cmake 3.10 or later
- Windows:
  - WSL or MSVC
- Linux:
  - GCC

### Building

run `cmake .` in the root directory to generate the project files, then use `make` (Linux) or `nmake` (Windows) to build the library file.

By default, making the project will also build a test_alpha_tools executable, which will run the built-in tests if executed.
