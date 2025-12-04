#ifndef EVAL_H
#define EVAL_H

#include <iostream>
#include <math.h>
#include <cassert>
#include "board.h"

inline float whiteInput[768];
inline float blackInput[768];

inline float whiteAccumulator[1024];
inline float blackAccumulator[1024];

inline float whiteAccumulatorWeights[1024][768];
inline float blackAccumulatorWeights[1024][768];

inline float whiteAccumulatorBias[1024];
inline float blackAccumulatorBias[1024];

inline float whiteOutputWeights[1024];
inline float blackOutputWeights[1024];

inline float outputBias;

inline float evalTable[] = {1000, 9, 5, 3.2, 3, 1};

inline float eval() {
    // return 0.0;
    float eval = 0;

    for (int j = 0; j < 6; j++) {
        eval += evalTable[j] * (cnt(b.boards[0][j]) - cnt(b.boards[1][j]));
    }

    return eval;

    double draw0 = 0.8;
    double c = 0.6;
    double k = 1.2;
    double pDraw = draw0 * exp(-c * abs(eval));
    double decisive = 1 - pDraw;
    double sig = 1 / (1 + exp(-k * eval));
    double pWin = decisive * sig;
    double pLoss = decisive * (1 - sig);
    double score = pWin - pLoss;
    return score;
    return eval;
}

#endif
