# LMC Emulator

An emulator for the [Little Man Computer](https://littlemancomputer.co.uk/), a simple hyprothetical machine that executes assembly instructions, written in C and Python. 
The emulator interprets LMC assembly instructions, executes them step by step, outputting the results to stdout.

## Requirements

- Python version 3.9 or later
- CMake and a suitable C toolchain
- Make

## Installation

```
git clone https://github.com/jdf18/LMC_Emulator.git
mkdir build
cd build
cmake ..
make
```

## Usage
Place the compiled .lmc file in the project directory (e.g. `./code.lmc`)

### Executing the .lmc code for a single input value

Call `./build/LMCEmulator ./code.lmc VALUE` to simulate the computer for the input value provided. 

### Testing for a series of inputs

The code in `collatz_test.py` shows how to test for a series of inputs that the correct outputs are produced.\
It checks that the output for any input into the program returns the correct sequence of numbers produced when following the [Collatz conjecture](https://en.wikipedia.org/wiki/Collatz_conjecture).

Run the python script, passing in the path to the .lmc file as the first parameter.
```
python3 collatz_test.py ./code.lmc
```

