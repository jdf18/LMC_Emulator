# LMC Emulator

# Installation

```
git clone https://github.com/jdf18/LMC_Emulator.git
mkdir build
cd build
cmake ..
make
```

# Usage
Place the compiled .lmc file in the project directory (e.g. `./code.lmc`)

## Executing the .lmc code for a single input value

Call `./build/LMCEmulator ./code.lmc VALUE` 

The executable will be called `LMCEmulator.exe` in Windows.

## Testing for a series of inputs

The code in collatz_test.py shows how to do this for the sequence produced by the collatz conjecture.

Run the python script, passing in the path to the .lmc file as the first parameter.
```
python3 test.py ./code.lmc
```

