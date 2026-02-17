# Across the River — C Solution (Fox, Chicken, Corn Puzzle)

## Overview

This project implements a solver for the classic river‑crossing logic puzzle:

> A person must transport a fox, a chicken, and a sack of corn across a river using a boat that can only carry the person and one item at a time.
>
> Constraints:
>
> * The fox cannot be left alone with the chicken.
> * The chicken cannot be left alone with the corn.
> * The person must always be present to prevent those conflicts.

The program automatically finds a valid sequence of moves using a **Depth‑First Search (DFS)** backtracking algorithm and prints every step of the solution.

---

## How It Works

### State Representation

Each actor has two fields:

* `first_side`  → left river bank
* `second_side` → right river bank

Value meaning:

```
1 = actor is on that side
0 = actor is not on that side
```

There are four actors:

* Person
* Chicken
* Fox
* Corn

So the complete state is defined by **4 binary values** → 2⁴ = 16 possible states.

The program encodes a state as a number from 0 to 15 using bit packing:

```
state = C F O P  (binary)
```

This allows the solver to track visited states and avoid infinite loops.

---

## Algorithm

The solver uses **recursive DFS with backtracking**:

1. Print current state
2. Check if goal state reached
3. Encode state and mark as visited
4. Try all possible moves:

   * Person crosses alone
   * Person + Chicken
   * Person + Fox
   * Person + Corn
5. Reject invalid states (predation rules)
6. Backtrack if dead end

### Validity Rule

A state is invalid if:

* Chicken and Fox alone without Person
* Chicken and Corn alone without Person

---

## Program Structure

| Function           | Purpose                          |
| ------------------ | -------------------------------- |
| `Title()`          | Displays program description     |
| `Initialization()` | Sets initial positions           |
| `Test()`           | Checks if a state is safe        |
| `Test_end()`       | Checks if goal state reached     |
| `PrintState()`     | Prints formatted table of actors |
| `moveActor()`      | Performs a move                  |
| `encodeState()`    | Converts state to 4‑bit integer  |
| `solve()`          | Recursive DFS solver             |
| `main()`           | Entry point                      |

---

## Compilation & Execution

### Compile (Linux / macOS / WSL)

```
gcc river.c -o river
```

### Run

```
./river
```

### Windows (MinGW)

```
gcc river.c -o river.exe
river.exe
```

---

## Example Output (shortened)

```
Across the River

STEP 1
Chicken 1 | 0
Fox     1 | 0
Corn    1 | 0
Person  1 | 0

STEP 2
...

Solution found!
```

Each step shows which side of the river each actor is on.

---

## Complexity

State space: 16 states

Worst‑case time complexity: O(states × moves)
= O(16 × 4) → effectively constant time

Memory usage: O(states)

The algorithm is guaranteed to terminate quickly due to the small finite state space.

---

## Why DFS + Backtracking?

Advantages:

* Simple to implement
* Guaranteed solution discovery
* Easy to visualize steps
* No unnecessary memory overhead (compared to BFS queue storage)

---

## Possible Improvements

* Store and print the move descriptions ("Take chicken", etc.)
* Implement BFS to guarantee shortest solution
* Add graphical visualization
* Convert to generic solver for any river crossing puzzle
* Add command‑line step delay animation

---

## Author Notes

This project was written as a solution to a programming challenge shared online. The goal was not only to solve the puzzle but to demonstrate:

* State encoding
* Recursion
* Backtracking
* Search algorithms in C

It serves as a compact example of how classical AI search problems can be modeled using low‑level languages.
