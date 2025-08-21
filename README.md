# Square Equation Solver

Pretty simple programm to solve square equations.

## Fast build and run

Make sure that you have `g++` before running.
Then run in terminal theese lines of code one by one:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre
./run.sh ./*.cpp
```

## Building

To build an executable you need to install `g++` compiler and then run:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre
./build.sh ./*.cpp
```

You can provide flags to executable after `-a` flag.

Example: `./run.sh ./*.cpp -a --some-flag`

## Testing

### Running tests

To run programm in testing mode you need to
start executable with `--self-check` flag.

Example: `./quadratic --self-check`

### Editing tests

All tests are located at tests.txt.

Every i-th line of this .txt contains input to i-th test.
You can edit this file with your favourite text editor.
