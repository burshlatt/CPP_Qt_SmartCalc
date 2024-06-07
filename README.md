## SmartCalc

### Dependencies

- CMake
- g++
- Google Test

### Installation

- Clone the repository
   ```bash
   git clone git@github.com:burshlatt/CPP_Qt_SmartCalc.git
   ```

- Go to the project folder
   ```bash
   cd CPP_Qt_SmartCalc
   ```

#### CMake

   ```bash
   mkdir build
	 cd build
   cmake ..
   make
   ./SmartCalc # or "open SmartCalc.app" (If you are running the MacOS operating system)
   ```

#### Make

1. **Build**: Compiles the SmartCalc application.
   ```bash
   make
   # or make build
   ```

2. **Install**: Installs the SmartCalc application.
   ```bash
   make install
   ```

3. **Test**: Runs the unit tests.
   ```bash
   make test
   ```

4. **Run**: Executes the SmartCalc application.
   ```bash
   make run
   ```

#### Makefile flags

- `build`: Builds the application.
- `install`: Installs the application.
- `run`: Runs the application.
- `uninstall`: Uninstalls the application.
- `clean`: Cleans build artifacts.
- `test`: Runs unit tests.
