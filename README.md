## Project Directory

This is the project directory for CSCI-3081, Program Design and Development. It implements an interactive image modifying tool with drawing and filtering functions. All codes and test are included in [src](https://github.com/yve-syyan/Image_Filtering/tree/master/src).

### CSE Lab Machines (Supported)

#### Build and Run

```bash
# Build the program with make
make
# Run the program
./build/bin/flashphoto
```
 
#### Check Style

```bash
# Using cpplint.py
make check-style
# Using cpplint-cse.sh
make check-style-cse
```

#### Run Tests

```bash
./build/test/gtests
```

#### Clean the Project

```bash
# Simply clean the project (for most situations)
make clean

# If there are catastrophic problems, especially with MinGfx, you can clobber everything
make clobber
```
