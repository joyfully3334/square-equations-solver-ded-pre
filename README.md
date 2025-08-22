# Square Equation Solver

Pretty simple programm to solve square equations.

## Fast build and run

Make sure that you have `g++` before running.
Then run in terminal theese lines of code one by one:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre
./build_and_run.sh ./*.cpp
```

## Building

To build an executable you need to install `g++` compiler and then run:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre
./build.sh ./*.cpp
```

You can provide flags to executable after `-a` flag.

Example: `./build_and_run.sh ./*.cpp -a --some-flag`

## Testing

### Running tests

To run programm in testing mode you need to
start executable with `--self-check` flag.

If you are useing build_and_run.sh script you need
tor pass `--self-check` flag after `-a` flag.

Example: `./build_and_run.sh ./*.cpp -a --self-check`

### Editing tests

All tests are located at tests.txt.

Each line consists of test before '@' and answers after '@'.
First number after '@' symbol stands for number of solutions.
This number may be '0', '1', '2' or '-1'(infinite).
It is an error if number after '@' is invalid.

Example:

```txt
x^2 + 2x + 1 @1 -1
x^2 + 0.5x @2 0
x + 3 @1 -3
3 @!
0 @0
x^2 + 5x - 3 @ 2 3 #ERROR
```

In this case ans0 and ans5 ignores.
