# MyLogger project
This repository holds the code base for the logger library along with other source code such as tests, samples, etc...

# Development environment:
- `sudo apt update && sudo apt install build-essential`
- Ubuntu 24.04
- Kernel: 6.11.0-17-generic
- Architecture: X86_64 (VM)
- `glibc`: 2.39
- `cmake`: 3.28.3
- `g++`: 13.3.0
- `python3`: 3.12.3

# Dev env preparations:
- Install GTest (on Debian machines):
- `sudo apt-get install libgtest-dev`
- `cd /usr/src/googletest/`
- `sudo mkdir build && cd build`
- `sudo cmake ..`
- `sudo make install`

# Build the project:
- Clone the git repo.
- Navigate to the root folder of the repo.
- `mkdir build && cd build && cmake .. && make`
- OPTIONAL: Run GTest based unit test (form within the `build` folder):
- `tests/unitTests`

# Run the executable:
- From within the `build` folder from earlier:
- `src/mainApplication`
