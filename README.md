# Kinetic Hero Chess Engine

Kinetic Hero is a lightweight and highly efficient chess engine written in modern C++23. Built with a focus on both algorithmic elegance and practical performance, it explores advanced chess AI concepts such as move generation, evaluation, and Monte Carlo Tree Search (MCTS)–style decision making. 

---

## Features

- **Bitboard Representation**  
  Efficiently tracks pieces, attacks, and board state for both colors using 64-bit integers.

- **FEN Parsing**  
  Load and export positions using Forsyth–Edwards Notation (FEN).

- **Comprehensive Move Generation**  
  - Handles all standard chess rules: castling, en passant, promotions.  
  - Supports checks, pins, and double-check scenarios.  
  - Generates legal moves with filtering for illegal positions.

- **Search and Evaluation**  
  - MCTS-style search with PUCT-based move selection.  
  - Lightweight evaluation function for assessing positions.  
  - Supports both fixed-time and time-control-based search.

- **Flexible Timing**  
  Allows searches constrained by either a fixed number of milliseconds or a time control with increments.

---

## Project Structure

```
.
├── src/
│   ├── board.h       # Board representation, move generation, FEN handling
│   ├── eval.h        # Position evaluation
│   ├── policy.h      # Policy priors for search
│   ├── search.h      # Search algorithms and tree management
│   └── main.cpp      # Entry point for UCI or CLI interaction
├── build/            # Object files generated during compilation
├── bin/              # Compiled engine binary
├── Makefile          # Build automation
└── README.md         # Project overview
```

---

## Building

Ensure you have a C++2b–compatible compiler (tested with `clang++`):

```
make       # Build the engine
make clean # Clean compiled files
```

The resulting executable will be located at `bin/engine`.

---

## Usage

Run the engine from the terminal:

```
./bin/engine
```

The engine can be used standalone or integrated with UCI-compatible GUIs. Available search functions:

- `search(TL)` — fixed-time search in milliseconds.
- `search(wtime, btime, winc, binc)` — search based on player clocks and increments.

---

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
