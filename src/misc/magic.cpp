#include <bits/stdc++.h>
#include <random>
#define ll unsigned long long
#define lsb(x) countl_zero(x)
#define on(x, i) ((x >> i) & 1)
using namespace std;

int rookDirs[] = {1, -1, 8, -8};
int bishopDirs[] = {9, 7, -9, -7};

ll rookBlockers[16384];
ll bishopBlockers[16384];
bool filled[16384];

ll rookAll[64];
ll bishopAll[64];

ll rookMagic[64];
ll bishopMagic[64];

mt19937 rng((ll)chrono::steady_clock::now().time_since_epoch().count());

ll get(ll L, ll R) {
    return uniform_int_distribution<ll>(L, R)(rng);
}

void magic() {
    for (int i = 0; i < 64; i++) {
        rookAll[i] = 0;
        bishopAll[i] = 0;
        
        // rook
        for (int j : rookDirs) {
            for (int k = 1; i + j * k < 64 && i + j * k >= 0; k++) {
                int diff = (i + j * k) % 8 - (i + j * (k - 1)) % 8;
                if (abs(diff) > 1) break; // don't move off the board
                if (j == -1 && (i + j * k) % 8 == 0) break;
                if (j == 1 && (i + j * k) % 8 == 7) break;
                if (j == 8 && (i + j * k) >= 56) break;
                if (j == -8 && (i + j * k) <= 7) break;

                rookAll[i] |= 1ULL << (i + j * k);
            }
        }

        int L = popcount(rookAll[i]);

        for (int j = 0; j < (1 << L); j++) {
            ll mask = rookAll[i];
            ll blocker = 0;
            for (int k = 0; k < L; k++) {
                if (on(j, k)) {
                    blocker |= 1ULL << lsb(mask);
                }
                mask &= mask - 1;
            }

            rookBlockers[j] = blocker;
        }

        while (true) {
            ll test = get(0, LLONG_MAX);
            memset(filled, 0, sizeof(filled));
            bool valid = true;
            for (int j = 0; j < (1 << L); j++) {
                ll blocker = rookBlockers[j];
                ll ind = (blocker * test) >> (64 - 14);
                if (filled[ind]) {
                    valid = false;
                    break;
                }
                filled[ind] = 1;
            }

            if (valid) {
                rookMagic[i] = test;
                break;
            }
        }

        // bishop
        for (int j : bishopDirs) {
            for (int k = 1; i + j * k < 64 && i + j * k >= 0; k++) {
                int diff = (i + j * k) % 8 - (i + j * (k - 1)) % 8;
                if (abs(diff) > 1) break; // don't move off the board
                if (j == 9 && (i + j * k) % 8 == 7) break;
                if (j == 7 && (i + j * k) % 8 == 0) break;
                if (j == -9 && (i + j * k) % 8 == 0) break;
                if (j == -7 && (i + j * k) % 8 == 7) break;

                bishopAll[i] |= 1ULL << (i + j * k);
            }
        }

        L = popcount(bishopAll[i]);
        vector<ll> bishopBlockers(1 << L);
        
        for (int j = 0; j < (1 << L); j++) {
            ll mask = bishopAll[i];
            ll blocker = 0;
            for (int k = 0; k < L; k++) {
                if (on(j, k)) {
                    blocker |= 1ULL << lsb(mask);
                }
                mask &= mask - 1;
            }

            bishopBlockers[j] = blocker;
        }

        while (true) {
            ll test = get(0, LLONG_MAX);
            memset(filled, 0, sizeof(filled));
            bool valid = true;

            for (int j = 0; j < (1 << L); j++) {
                ll blocker = bishopBlockers[j];
                ll ind = (blocker * test) >> (64 - 14);
                if (filled[ind]) {
                    valid = false;
                    break;
                }
                filled[ind] = 1;
            }

            if (valid) {
                bishopMagic[i] = test;
                break;
            }
        }
    }
}

int main() {
    magic(); // sliding precomp

    cout << "Rook magic numbers:\n";
    cout << "{";
    for (int i = 0; i < 64; i++) {
        cout << rookMagic[i] << ", ";
    }
    cout << "}\n";

    cout << "Bishop magic numbers:\n";
    cout << "{";
    for (int i = 0; i < 64; i++) {
        cout << bishopMagic[i] << ", ";
    }
    cout << "}\n";

    return 0;
}