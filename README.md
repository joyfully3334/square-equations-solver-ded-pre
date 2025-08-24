# Square Equation Solver

Pretty simple programm to solve square equations.

## Options

--help       Display this information.
--self-check Check tests from tests.txt and tests_parse.
--silent     Dont print welocme message.
--parse      Use parsing version of programm.

## Fast build and run

Make sure that you have `g++` before running.
Then run in terminal theese lines of code:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre
./build_and_run.sh ./*.cpp
```

You can provide flags to executable after `-a` flag.

Example: `./build_and_run.sh ./*.cpp -a --some-flag`

## Building

To build an executable you need to install `g++` compiler and then run:

```bash
git clone github.com/joyfully3334/square-equations-solver-ded-pre
cd ~/square-equations-solver-ded-pre/
make
```

To clean executable and object files run:

```bash
cd ~/square-equations-solver-ded-pre/
make clean
```

## Testing

### Running tests

To run programm in testing mode you need to
start executable with `--self-check` flag.

If you are using build_and_run.sh script you need
tor pass `--self-check` flag after `-a` flag.

Example: `./build_and_run.sh ./*.cpp -a --self-check`

### Editing tests

All tests are located at tests.txt for standard version
and tests_parse.txt for parsing version.

Each line consists of test before '@' and answers after '@'.
First number after '@' symbol stands for number of solutions.
This number may be '0', '1', '2' or '-1'(infinite).
