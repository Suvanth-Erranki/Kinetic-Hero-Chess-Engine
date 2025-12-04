#ifndef SEARCH_H
#define SEARCH_H


#include "board.h"
#include "eval.h"
#include "policy.h"

#include <iostream>
#include <cstddef>
#include <cassert>
#include <array>
#include <chrono>
using namespace std;
using namespace chrono;

struct Node {
    int parMove; // move from prev to curr state
    int par; // index of par

    int N = 0; // # of evals
    float score = 0; // sum of all evals
    
    int firstChild; // indices of all children moves in tree
    int moveLen = 0;
};

// const int SIMS = 5e7;
inline const int SZ = 5e8;
inline const int MOVE_TOT = 5e8;
inline Node* tree = new Node[SZ];
inline Move* allMoves = new Move[MOVE_TOT];
inline int* allChildren = new int[MOVE_TOT];
inline float* priors = new float[256];

// Node tree[SZ];
// Move allMoves[MOVE_TOT];
// int allChildren[MOVE_TOT];

inline int treeInd = 1;
inline int allMovesInd = 0;

inline int SQRT(int x) {
    int res = 0;
    int bit = 1 << 30;

    while (bit > x) bit >>= 2;
    while (bit) {
        if (x >= res + bit) {
            x -= res + bit;
            res = (res >> 1) + bit;
        } else {
            res >>= 1;
        }
        bit >>= 2;
    }
    return res;
}

inline void expandLeaf(int currNode) {
    tree[currNode].firstChild = allMovesInd;
    allMovesInd = b.genMoves(b.turn, allMoves, allMovesInd);
    tree[currNode].moveLen = allMovesInd - tree[currNode].firstChild;

    bool holes = 0;
    for (int j = tree[currNode].firstChild; j < tree[currNode].firstChild + tree[currNode].moveLen; j++) {
        if (!b.isLegal(allMoves[j])) {
            allChildren[j] = -1;
            holes = 1;
            continue;
        }

        tree[treeInd] = Node();
        tree[treeInd].parMove = j;
        tree[treeInd].par = currNode;
        allChildren[j] = treeInd;
        treeInd++;
    }

    // Filter out illegal moves
    if (holes) {
        int shiftInd = tree[currNode].firstChild;

        for (int j = tree[currNode].firstChild; j < tree[currNode].firstChild + tree[currNode].moveLen; j++) {
            if (allChildren[j] != -1) {
                allMoves[shiftInd] = allMoves[j];
                allChildren[shiftInd] = allChildren[j];
                tree[allChildren[j]].parMove = shiftInd;
                shiftInd++;
            }
        }

        allMovesInd = shiftInd;
        tree[currNode].moveLen = allMovesInd - tree[currNode].firstChild;
    }
}

inline void expand() {
    int currNode = 0;
    Board originalB = b;

    bool leafNodeTerminal = false;
    bool pvPath = true;

    // Selection
    while (tree[currNode].N > 0) {

        if (tree[currNode].N == 1) {
            expandLeaf(currNode);
        }

        if (tree[currNode].moveLen == 0) {
            leafNodeTerminal = true;
            break;
        }

        int sqSig = 0;

        for (int j = tree[currNode].firstChild; j < tree[currNode].firstChild + tree[currNode].moveLen; j++) {
            int childInd = allChildren[j];
            sqSig += tree[childInd].N;
        }

        sqSig = SQRT(sqSig);

        int bestChild = -1;
        float bestScore = -1e9;

        int mostVisCnt = -1;
        int mostVisChild = 0;

        getPriors(priors, tree[currNode].moveLen);

        for (int j = tree[currNode].firstChild; j < tree[currNode].firstChild + tree[currNode].moveLen; j++) {
            int childInd = allChildren[j];
            // PUCT
            float P = priors[j - tree[currNode].firstChild]; // Policy network prior
            float Q = 0L;
            float denom = 1.0L + tree[childInd].N;

            if (tree[childInd].N > 0) {
                Q = tree[childInd].score / tree[childInd].N;
                if (b.turn == 1) {
                    Q = -Q;
                }
            }

            // mitigate tactical blunder moves by doing a wider search on the PV
            float C = 2.5f;

            float score = Q + C * P * sqSig / denom;

            if (score > bestScore) {
                bestScore = score;
                bestChild = j;
            }

            if (tree[childInd].N > mostVisCnt) {
                mostVisChild = j;
                mostVisCnt = tree[childInd].N;
            }
        }

        if (bestChild != mostVisChild) {
            pvPath = false;
        }
        
        b.makeMove(allMoves[bestChild]);
        currNode = allChildren[bestChild];
    }

    // Evaluate the position
    float leafEval = eval(); // Value network

    // Backpropagation
    while (true) {
        tree[currNode].N++;
        tree[currNode].score += leafEval;
        
        if (currNode == 0) break;

        // b.unmakeMove(allMoves[tree[currNode].parMove]);
        currNode = tree[currNode].par;
    }

    b = originalB;
}

inline Move search(int TL) {
    auto end = steady_clock::now() + chrono::milliseconds(TL - 100);
    tree[0] = Node(); 
    while (treeInd < SZ && steady_clock::now() < end) {
        expand();
    }

    cout << "info Total # of nodes explored: " << treeInd << "\n";
    cout << "info Speed: " << (1.0f * treeInd / TL * 1000) << "NPS\n";

    int bestMoveInd = -1;
    int mostChildVis = -1;

    for (int i = tree[0].firstChild; i < tree[0].firstChild + tree[0].moveLen; i++) {
        int childInd = allChildren[i];
        float N = tree[childInd].N;

        // cout << "info Move #" << i << " - " << allMoves[i] << " ; Visits - " << tree[childInd].N << "; Avg Score - " << (tree[childInd].score / N) << "\n";

        if (tree[childInd].N > mostChildVis) {
            mostChildVis = tree[childInd].N;
            bestMoveInd = i;
        }

    }

    Move bestMove = allMoves[bestMoveInd];
    return bestMove;
}

inline Move search(int wtime, int btime, int winc, int binc) {
    int TL = 0;
    
    if (b.turn == 0) {
        TL = wtime / 10;
    }
    else {
        TL = btime / 10;
    }

    return search(TL);
}

#endif