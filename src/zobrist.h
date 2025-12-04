#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "board.h"
#include <chrono>
#include <random>
#include <iostream>

// mt19937_64 rng((ll) chrono::steady_clock::now().time_since_epoch().count());
const ll seed = 53;
mt19937_64 rng(seed);

class Zobrist {

    public:
        ll board_H[12][64];
        ll wCastleK_H[2];
        ll wCastleQ_H[2];
        ll bCastleK_H[2];
        ll bCastleQ_H[2];
        ll enp_H[8];

        Zobrist() {
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 64; j++) {
                    board_H[i][j] = rng();
                }
            }

            for (int i = 0; i < 2; i++) {
                wCastleK_H[i] = rng();
                wCastleQ_H[i] = rng();
                bCastleK_H[i] = rng();
                bCastleQ_H[i] = rng();
            }

            for (int i = 0; i < 8; i++) {
                enp_H[i] = rng();
            }
        }
};
#endif