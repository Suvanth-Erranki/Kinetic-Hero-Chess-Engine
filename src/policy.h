#ifndef POLICY_H
#define POLICY_H

#include <iostream>
#include "board.h"

inline void getPriors(float* priors, int n) {
    // add priors here
    for (int i = 0; i < n; i++) {
        priors[i] = 1.0f / n;
    }
}

#endif