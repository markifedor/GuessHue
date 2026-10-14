# CSCI 200: Final Project - Guess Hue?

#### By Mark Fedorchuk 

May 4th, 2023

## Overview

"Guess Hue?" is a color guessing game. You're given a color and you have to guess it's RGB values. Each value goes up by 15 as to reduce the number of colors to guess from 16,777,216 to 4913. 

The color you are guessing is displayed in the circle above the RGB value inputs. Inputting guesses is done through clicking on the arrows each color value and submitting with the green check box. The game is reset by clicking on the red reset button (twice). The results of your guess is displayed in a terminal window to the side.

## Building "GuessHue?" from Source

This project uses CMake with `FetchContent` to download and compile SFML 2.6.2 automatically during the build process—no manual SFML installation or setup is required.

---

### Prerequisites

Choose the platform instructions below to install a C++ compiler and CMake:

#### Windows (MSYS2 / MinGW)

1. Install [MSYS2](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal and install the build tools:

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-make
   ```

3. Add `C:\msys64\ucrt64\bin` to your system `PATH` environment variable.

#### macOS

Install the Xcode Command Line Tools and CMake via [Homebrew](https://brew.sh/):

```bash
xcode-select --install
brew install cmake
```

#### Linux (Ubuntu / Debian)

Install the standard C++ compiler toolchain along with SFML's required system development libraries:

```bash
sudo apt update
sudo apt install build-essential cmake libx11-dev libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev
```

---

### Build Instructions

1. **Clone the Repository**

   ```bash
   git clone [https://github.com/your-username/GuessHue.git](https://github.com/your-username/GuessHue.git)
   cd GuessHue
   ```

2. **Configure the Project**

   * **Windows (MinGW / MSYS2):**

     ```powershell
     cmake -B build -G "MinGW Makefiles"
     ```

   * **Linux / macOS:**

     ```bash
     cmake -B build
     ```

3. **Compile the Executable**

   ```bash
   cmake --build build
   ```

---

### Running the Game

Upon completion, `GuessHue.exe` (or `GuessHue` on Linux/macOS) is generated directly in the project root folder alongside the `data/` assets directory.

* **Windows:**

  ```powershell
  .\GuessHue.exe
  ```

* **Linux / macOS:**

  ```bash
  ./GuessHue
  ```
