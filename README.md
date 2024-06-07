# SmartCalc

## Dependencies

- Make
- CMake
- Qt6
- g++
- Google Test

## Installation

- Clone the repository
   ```bash
   git clone https://github.com/burshlatt/CPP_Qt_SmartCalc.git
   ```

- Go to the project folder
   ```bash
   cd CPP_Qt_SmartCalc
   ```

#### CMake

- Installation via CMake
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./SmartCalc # or "open SmartCalc.app" (If you are running the MacOS operating system)
   ```

#### Make

- Installation via Make
   ```bash
   make
   make install
   make test # optional
   make run
   ```

#### Makefile flags

- `build`: Builds the application.
- `install`: Installs the application.
- `run`: Runs the application.
- `uninstall`: Uninstalls the application.
- `clean`: Cleans build artifacts.
- `test`: Runs unit tests.
