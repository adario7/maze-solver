# Maze solver

Simple C++ implementation of a maze solver:

- reads a maze from standard input
- locates start and end positions
- runs a breadth-first search sourced at the start position
- terminates upon reaching the end position
- saves backtracking information during the search
- uses backtracking information to reconstruct the shortest path
- displays the path as a list of steps, if such path exists

## Running the code

Compile using `make` and `g++`:

```bash
make
```

Solve the first sample maze:

```bash
cat input1
make run < input1
```




