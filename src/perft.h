#ifndef PERFT_H
#define PERFT_H


#include "board.h"
#include <iostream>
#include <functional>
#include <cstring>
#include <chrono>
using namespace std;

inline void perft(int depth) {
    function<ll(int)> count = [&] (int ply) -> ll {
        if (ply == depth) return 1;
        ll nodes = 0;
        Move moves[256];
        int n = b.genMoves(b.turn, moves);
        for (int i = 0; i < n; ++i) {
            Move m = moves[i];
            if (b.makeMove(m)) {
                nodes += count(ply + 1);
                b.unmakeMove(m);
            }
        }
        return nodes;
    };

    auto start = chrono::high_resolution_clock::now();
    Move rootMoves[256];
    int nRoot = b.genMoves(b.turn, rootMoves);

    long long tot = 0;
    for (int i = 0; i < nRoot; ++i) {
        Move m = rootMoves[i];
        if (b.makeMove(m)) {
            long long cnt = count(1);
            cout << rootMoves[i].toString() << " " << cnt << "\n";
            tot += cnt;
            b.unmakeMove(m);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    ll elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "\n";
    cout << "Nodes searched: " << tot << "\n";
    cout << "Time: " << elapsed << "ms" << endl;
}


#endif