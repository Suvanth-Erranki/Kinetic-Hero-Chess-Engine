# Kinetic Hero Chess Engine

Kinetic Hero is a lightweight and highly efficient chess engine written in C++23, utilizing advanced move generation and Monte Carlo Tree Search (MCTS)–style decision making. 

## Features

- **Board Representation**
   - Efficient representation of chess positions in `board.h`.
   - Supports move generation, legality checks, and move execution/unexecution.

- **Monte Carlo Tree Search (MCTS)**
   - Implemented in `search.h`.
   - Uses **PUCT (Predictor + Upper Confidence bound applied to Trees)** to balance exploration and exploitation.
   - Maintains visit counts (`N`) and accumulated scores (`score`) at each node.
   - Expands leaf nodes and filters out illegal moves.
   - Uses policy priors from `policy.h` to guide move selection.

- **High-Performance Optimizations**
   - Preallocated memory pools for nodes and moves to avoid dynamic allocation overhead.
   - In-place filtering of illegal moves during expansion.
   - Fast integer square root function used for exploration term computation.
   - Designed to explore millions of positions efficiently.

- **Time-Controlled Search**
   - Supports fixed-time search (`search(int TL)`).
   - Supports chess clock-aware search (`search(int wtime, int btime, int winc, int binc)`).
   
- **Evaluation (WIP)**
   - `eval.h` contains position evaluation functions.
   - Can be replaced with a neural network-based evaluator for stronger play.

- **Policy Network (WIP)**
   - Generates move priors to bias MCTS towards promising moves.
   - Supports integration with external policy models.
   
- **Debugging and Info**
   - Outputs node count, speed (nodes per second), and optionally detailed move statistics.

## Todo:

- Add Zobrist hashing and 3-fold repetition/draw detection
- Multithreaded MCTS search
- Try MCTS variants (progressive bias, RAVE, virtual loss)
- Train Policy and Value network weights (currently use Apple Silicon M2, rendering GPU training problematic) 
- Improve leaf evaluation (material + positional heuristics)
- Optimize memory usage and speed (tree, moves, priors)

---

## Building

The default compilation uses `clang`, but it is replacable with `g++`.

```
make clean && make
```

The resulting executable will be located at `bin/engine`.

## Usage

Run the engine from the terminal:

```
./bin/engine
```

The engine can be used standalone or integrated with UCI-compatible GUIs. Available search functions:

- `search(TL)` — fixed-time search in milliseconds.
- `search(wtime, btime, winc, binc)` — search based on player clocks and increments.

## How It Works

1. **Board Class**  
   Manages board state using bitboards, including piece locations, castling rights, en passant, and move counters.

2. **Move Generation**  
   Generates all possible moves, handles special rules, and filters illegal moves.

3. **Search**  
   Uses a Monte Carlo Tree Search approach:
   - Selection via PUCT formula with policy priors.
   - Expansion of unexplored moves.
   - Evaluation using a simple scoring function.
   - Backpropagation of scores through the tree.

4. **Evaluation**  
   Provides a lightweight position assessment. Can be extended for more advanced heuristics or neural network integration.

---

## License

MIT License - free for use, modification, and redistribution.
