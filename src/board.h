#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <array>

#define ll unsigned long long
#define lsb(x) __builtin_ctzll(x)
#define on(x, i) ((x >> (i)) & 1)
#define cnt(x) (__builtin_popcountll(x))
using namespace std;

int sqNum(char file, char rank);
string numSq(int num);

inline constexpr int kingShifts[] = {8, 9, 7, -8, -9, -7, 1, -1};
inline constexpr int queenDirs[] = {1, -1, 8, -8, 9, 7, -9, -7};
inline constexpr int rookDirs[] = {1, -1, 8, -8};
inline constexpr int bishopDirs[] = {9, 7, -9, -7};
inline constexpr int knightShifts[] = {17, 15, 10, 6, -17, -15, -10, -6};

inline constexpr char numPieceChar[] = {'k', 'q', 'r', 'b', 'n', 'p'};

constexpr array<ll, 64> rookMagic = {4548357378587538164, 6785849867466700775, 1358183705661486896, 1172449196469878046, 7645966256185424001, 3066573916567414305, 703597934859087762, 7751453351102005081, 8384682732186318697, 3826743312734733894, 8485321100807313231, 3759280488877944326, 5881551016435485466, 3485028974523818276, 4533260459425739244, 3563975851759248842, 2330422058768396032, 9208119780330356872, 2395704805117732030, 1679773921115252028, 6299865935630183714, 1646067019858112509, 1705394503400803875, 4885759738359752317, 696321744741806204, 4187043072695226888, 1230444673303646736, 6784658403487034616, 4432793895558438180, 4143295430959029343, 1173165387195267991, 2131231181605104813, 2113039890094873620, 7190553575072908853, 2547817263847333892, 7529157747799688548, 3904793038863636872, 4924590829322230391, 986931088898005854, 652517981174052275, 1295890804884543594, 8624239531234471161, 704057520613804391, 6874729934571182710, 7836475723992148296, 5463683595039980593, 3955163130835410647, 3735896619694148533, 6656488861986981704, 3185569458260355832, 4139541479410874853, 1004063651997962230, 2652293593194645990, 1450298371605933897, 243145935565964278, 6201102452051742207, 411420320029265914, 4238928103705590022, 7045702171849964006, 8217178492007333541, 7284089224843415358, 6659384304390311286, 4577438417447067979, 2636584148173024638};
constexpr array<ll, 64> bishopMagic ={4983872475783700162, 4477306266342548874, 4271007773914020043, 1485136442319009014, 1314110460885159982, 3608970327774410045, 8472096887139523378, 4270974762318242055, 2179609196258188386, 7986959408292615908, 5010225570201690465, 753788893168887727, 8207781474628542327, 724165032778291972, 7129394244531448359, 2369042138198945410, 2297844356150793076, 481264676151983121, 7027735372548576631, 7431156687166181960, 2731361630384153853, 6242427283605752532, 4194904901582341531, 7940015723142135777, 3021085398018779288, 7730242532903679497, 2024825576372522518, 867568584277229884, 1961041442507757996, 7698966882506125433, 2650352984496512616, 3951521248142231384, 3427681982739257546, 8029631771476707067, 501216337481485879, 2359288516143439838, 4719918472750985329, 2569558146674676164, 3511411139150614861, 9004826903160801347, 6733897079117835744, 1006901594479184779, 212410608505648348, 5382409475917527555, 63346272135021346, 1926059573166103163, 8256377585449395243, 1626465918196878398, 3300069397885724207, 5988548831500593312, 5407319863419683706, 4999115103524812545, 1846217321325821961, 7630292979562369851, 2684708403067675737, 2607607984659361297, 8296903230099205707, 4237827472847228860, 7096530704187260875, 1438511422749021650, 7872192575961488351, 2640391775106416086, 6180738567046710978, 6620166359117914738};

constexpr array<ll, 64> kingPrecomp() {
    array<ll, 64> kingAtk;
    for (int i = 0; i < 64; i++) {
        kingAtk[i] = 0;
        
        if (i + 8 < 64) kingAtk[i] |= 1ULL << (i + 8);
        if (i - 8 >= 0) kingAtk[i] |= 1ULL << (i - 8);
        if (i + 1 < 64 && (i & 7) != 7) kingAtk[i] |= 1ULL << (i + 1);
        if (i - 1 >= 0 && (i & 7) != 0) kingAtk[i] |= 1ULL << (i - 1);
        if (i + 9 < 64 && (i & 7) != 7) kingAtk[i] |= 1ULL << (i + 9);
        if (i + 7 < 64 && (i & 7) != 0) kingAtk[i] |= 1ULL << (i + 7);
        if (i - 9 >= 0 && (i & 7) != 0) kingAtk[i] |= 1ULL << (i - 9);
        if (i - 7 >= 0 && (i & 7) != 7) kingAtk[i] |= 1ULL << (i - 7);
    }

    return kingAtk;
}

constexpr array<ll, 64> rookAllPrecomp() {
    array<ll, 64> rookAll;
    for (int i = 0; i < 64; i++) {
        rookAll[i] = 0;

        for (int j : rookDirs) {
            for (int k = 1; i + j * k < 64 && i + j * k >= 0; k++) {
                int diff = ((i + j * k) & 7) - ((i + j * (k - 1)) & 7);
                if (abs(diff) > 1) break; // don't move off the board
                if (j == -1 && ((i + j * k) & 7) == 0) break;
                if (j == 1 && ((i + j * k) & 7) == 7) break;
                if (j == 8 && (i + j * k) >= 56) break;
                if (j == -8 && (i + j * k) <= 7) break;

                rookAll[i] |= 1ULL << (i + j * k);
            }
        }
    }

    return rookAll;
}

inline array<ll, 64> rookAll = rookAllPrecomp();

constexpr array<array<ll, 16384>, 64> rookMovesPrecomp() {
    array<array<ll, 16384>, 64> rookMoves;
    for (int i = 0; i < 64; i++) {
        int L = cnt(rookAll[i]);

        for (int j = 0; j < (1 << L); j++) {
            ll mask = rookAll[i];
            ll blocker = 0;
            for (int k = 0; k < L; k++) {
                if (on(j, k)) {
                    blocker |= 1ULL << lsb(mask);
                }
                mask &= mask - 1;
            }

            int ind = (blocker * rookMagic[i]) >> (64 - 14);
            rookMoves[i][ind] = 0;

            for (int k : rookDirs) {
                for (int l = 1; i + k * l < 64 && i + k * l >= 0; l++) {
                    int diff = abs((i + k * l) & 7) - ((i + k * (l - 1)) & 7);
                    if (abs(diff) > 1) break;
                    
                    rookMoves[i][ind] |= 1ULL << (i + k * l);
                    if (on(blocker, i + k * l)) break;
                }
            }
        }
    }

    return rookMoves;
}

constexpr array<ll, 64> bishopAllPrecomp() {
    array<ll, 64> bishopAll;
    for (int i = 0; i < 64; i++) {
        bishopAll[i] = 0;

        for (int j : bishopDirs) {
            for (int k = 1; i + j * k < 64 && i + j * k >= 0; k++) {
                int diff = ((i + j * k) & 7) - ((i + j * (k - 1)) & 7);
                if (abs(diff) > 1) break; // don't move off the board
                if (j == 9 && ((i + j * k) & 7) == 7) break;
                if (j == 7 && ((i + j * k) & 7) == 0) break;
                if (j == -9 && ((i + j * k) & 7) == 0) break;
                if (j == -7 && ((i + j * k) & 7) == 7) break;

                bishopAll[i] |= 1ULL << (i + j * k);
            }
        }
    }

    return bishopAll;
}

inline array<ll, 64> bishopAll = bishopAllPrecomp();

constexpr array<array<ll, 16384>, 64> bishopMovesPrecomp() {
    array<array<ll, 16384>, 64> bishopMoves;
    for (int i = 0; i < 64; i++) {
        int L = cnt(bishopAll[i]);

        for (int j = 0; j < (1 << L); j++) {
            ll mask = bishopAll[i];
            ll blocker = 0;
            for (int k = 0; k < L; k++) {
                if (on(j, k)) {
                    blocker |= 1ULL << lsb(mask);
                }
                mask &= mask - 1;
            }

            int ind = (blocker * bishopMagic[i]) >> (64 - 14);
            bishopMoves[i][ind] = 0;

            for (int k : bishopDirs) {
                for (int l = 1; i + k * l < 64 && i + k * l >= 0; l++) {
                    int diff = abs(((i + k * l) & 7) - ((i + k * (l - 1)) & 7));
                    if (abs(diff) > 1) break;
                    
                    bishopMoves[i][ind] |= 1ULL << (i + k * l);
                    if (on(blocker, i + k * l)) break;
                }
            }
        }
    }

    return bishopMoves;
}

constexpr array<ll, 64> knightPrecomp() {
    array<ll, 64> knightAtk;
    for (int i = 0; i < 64; i++) {
        knightAtk[i] = 0;
        
        if (i + 17 < 64 && (i & 7) != 7) knightAtk[i] |= 1ULL << (i + 17);
        if (i + 15 < 64 && (i & 7) != 0) knightAtk[i] |= 1ULL << (i + 15);
        if (i + 10 < 64 && (i & 7) < 6) knightAtk[i] |= 1ULL << (i + 10);
        if (i + 6 < 64 && (i & 7) > 1) knightAtk[i] |= 1ULL << (i + 6);
        if (i - 17 >= 0 && (i & 7) != 0) knightAtk[i] |= 1ULL << (i - 17);
        if (i - 15 >= 0 && (i & 7) != 7) knightAtk[i] |= 1ULL << (i - 15);
        if (i - 10 >= 0 && (i & 7) > 1) knightAtk[i] |= 1ULL << (i - 10);
        if (i - 6 >= 0 && (i & 7) < 6) knightAtk[i] |= 1ULL << (i - 6);
    }

    return knightAtk;
}

constexpr array<ll, 64> wPawnPrecomp() {
    array<ll, 64> wPawnAtk;
    for (int i = 0; i < 64; i++) {
        wPawnAtk[i] = 0;

        if (i - 9 >= 0 && (i & 7) != 0) wPawnAtk[i] |= 1ULL << (i - 9);
        if (i - 7 >= 0 && (i & 7) != 7) wPawnAtk[i] |= 1ULL << (i - 7);
    }

    return wPawnAtk;
}

constexpr array<ll, 64> bPawnPrecomp() {
    array<ll, 64> bPawnAtk;
    for (int i = 0; i < 64; i++) {
        bPawnAtk[i] = 0;

        if (i + 9 < 64 && (i & 7) != 7) bPawnAtk[i] |= 1ULL << (i + 9);
        if (i + 7 < 64 && (i & 7) != 0) bPawnAtk[i] |= 1ULL << (i + 7);
    }

    return bPawnAtk;
}

inline array<ll, 64> kingAtk = kingPrecomp();
inline array<array<ll, 16384>, 64> rookMoves = rookMovesPrecomp();
inline array<array<ll, 16384>, 64> bishopMoves = bishopMovesPrecomp();
inline array<ll, 64> knightAtk = knightPrecomp();
inline array<ll, 64> wPawnAtk = wPawnPrecomp();
inline array<ll, 64> bPawnAtk = bPawnPrecomp();

struct Move {
    int from; // 0-63
    int to;
    int board1; // ind
    int board2; // if capture

    bool pawnTwo = 0;
    bool enp = 0;
    bool castleK = 0;
    bool castleQ = 0;
    int promo = 0;

    bool oldKCastle;
    bool oldQCastle;
    bool oldPawnTwo;
    bool oldHalfMoves;

    Move() {}
    Move(int f, int t, int b1, int b2) : from(f), to(t), board1(b1), board2(b2) {}

    inline string toString() const {
        string res = numSq(from) + numSq(to);
        if (promo == 1) res += "q";
        if (promo == 2) res += "r";
        if (promo == 3) res += "b";
        if (promo == 4) res += "n";
        return res;
    }
};

inline int sqNum(char file, char rank) {
    int num = 8 * (rank - '1') + (file - 'a');
    return num;      
}

inline string numSq(int num) {
    char file = (num % 8) + 'a';
    char rank = (num / 8) + '1';
    return string(1, file) + rank;
}

inline ostream& operator<<(ostream& os, const Move& m) {
    return os << m.toString();
}

class Board {
    public:
        ll boards[2][6]; // k, q, r, b, n, p

        // where is king
        int kingSq[2];

        // can the king castle
        bool kCastle[2];
        bool qCastle[2];

        // file of a pawn pushed 2 to keep track for en passant
        int pawnTwo;

        bool turn;
        int halfMoves;

        
        inline ll whiteP() {
            return boards[0][0] | boards[0][1] | boards[0][2] | boards[0][3] | boards[0][4] | boards[0][5];
        }

        inline ll blackP() {
            return boards[1][0] | boards[1][1] | boards[1][2] | boards[1][3] | boards[1][4] | boards[1][5];
        }

        Board() {
            boards[0][0] = 0x0000000000000010;
            boards[0][1] = 0x0000000000000008;
            boards[0][2] = 0x0000000000000081;
            boards[0][3] = 0x0000000000000024;
            boards[0][4] = 0x0000000000000042;
            boards[0][5] = 0x000000000000FF00;

            boards[1][0] = 0x1000000000000000;
            boards[1][1] = 0x0800000000000000;
            boards[1][2] = 0x8100000000000000;
            boards[1][3] = 0x2400000000000000;
            boards[1][4] = 0x4200000000000000;
            boards[1][5] = 0x00FF000000000000;

            kCastle[0] = qCastle[0] = 1;
            kCastle[1] = qCastle[1] = 1;
            pawnTwo = -1;

            kingSq[0] = 4;
            kingSq[1] = 60;

            turn = 0;
            halfMoves = 0;
        }
        Board(string fen) {
            for (auto &i : boards) {
                for (auto &j : i) {
                    j = 0;
                }
            }

            kCastle[0] = kCastle[1] = 0;
            qCastle[0] = qCastle[1] = 0;
            pawnTwo = -1;

            turn = 0;
            halfMoves = 0;
            
            int square = 56;
            int rank = 7;
            int i = 0;
            for (i = 0; i < fen.size(); i++) {
                if (fen.at(i) >= '0' && fen.at(i) <= '9') {
                    int cnt = fen.at(i) - '0';
                    square += cnt;
                    continue;
                }

                if (fen[i] == '/') {
                    square = --rank * 8;
                    continue;
                }

                if (fen[i] == ' ') {
                    break;
                }

                switch (fen[i]) {
                    case 'P': boards[0][5] |= 1ULL << square; break;
                    case 'p': boards[1][5] |= 1ULL << square; break;
                    case 'R': boards[0][2] |= 1ULL << square; break;
                    case 'r': boards[1][2] |= 1ULL << square; break;
                    case 'N': boards[0][4] |= 1ULL << square; break;
                    case 'n': boards[1][4] |= 1ULL << square; break;
                    case 'B': boards[0][3] |= 1ULL << square; break;
                    case 'b': boards[1][3] |= 1ULL << square; break;
                    case 'Q': boards[0][1] |= 1ULL << square; break;
                    case 'q': boards[1][1] |= 1ULL << square; break;
                    case 'K': {
                        kingSq[0] = square;
                        boards[0][0] |= 1ULL << square; 
                        break;
                    }
                    case 'k': {
                        kingSq[1] = square;
                        boards[1][0] |= 1ULL << square; 
                        break;
                    }
                }

                square++;
            }

            i++; // skip space
            turn = (fen[i] == 'b');
            i += 2; // skip turn and space

            for (; i < fen.size(); i++) {
                if (fen[i] == ' ') {
                    break;
                }
                switch (fen[i]) {
                    case 'K': kCastle[0] = 1; break;
                    case 'Q': qCastle[0] = 1; break;
                    case 'k': kCastle[1] = 1; break;
                    case 'q': qCastle[1] = 1; break;
                }
            }

            i++; // skip space
            if (fen[i] != '-') {
                // int num = sqNum(fen[i], fen[i + 1]);
                // if (num < 24) num += 8; // white
                // else num -= 8; // black
                // pawnTwo = num;

                pawnTwo = fen[i] - 'a';
            }

            i += 2;
            if (i >= fen.size()) return;
            halfMoves = stoi(fen.substr(i));
            while (i < fen.size() && fen[i] >= '0' && fen[i] <= '9') {
                i++;
            }
            int fullMoves = stoi(fen.substr(i)); // unused
        }

        inline int at(int x, int color) {
            if (on(boards[color][0], x)) return 0;
            if (on(boards[color][1], x)) return 1;
            if (on(boards[color][2], x)) return 2;
            if (on(boards[color][3], x)) return 3;
            if (on(boards[color][4], x)) return 4;
            if (on(boards[color][5], x)) return 5;
            return -1;
        }

        inline bool attacked(int i, bool side) {
            ll all[] = {whiteP(), blackP()};
            ll allP = all[0] | all[1];
            int opp = side ^ 1;

            // king
            if (kingAtk[i] & boards[opp][0]) return true;

            // rook + 1/2 queen
            ll rookBlocker = rookAll[i] & allP;
            int ind1 = (rookBlocker * rookMagic[i]) >> (64 - 14);
            ll rookMask = rookMoves[i][ind1];
            rookMask &= ~all[side];

            if (rookMask & (boards[opp][1] | boards[opp][2])) return true;

            // bishop + 1/2 queen
            ll bishopBlocker = bishopAll[i] & allP;
            int ind2 = (bishopBlocker * bishopMagic[i]) >> (64 - 14);
            ll bishopMask = bishopMoves[i][ind2];
            bishopMask &= ~all[side];

            if (bishopMask & (boards[opp][1] | boards[opp][3])) return true;

            // knight
            if (knightAtk[i] & boards[opp][4]) return true;

            // pawn
            if (side == 0 && bPawnAtk[i] & boards[opp][5]) return true;
            if (side == 1 && wPawnAtk[i] & boards[opp][5]) return true;

            return false;
        }

        inline ll slidingChecks(bool side) {
            int i = kingSq[side];

            ll all[] = {whiteP(), blackP()};
            ll allP = all[0] | all[1];
            int opp = side ^ 1;
            ll ret = 0;

            // rook + 1/2 queen
            ll rookBlocker = rookAll[i] & allP;
            int ind1 = (rookBlocker * rookMagic[i]) >> (64 - 14);
            ll rookMask = rookMoves[i][ind1];
            rookMask &= ~all[side];

            ret |= (rookMask & (boards[opp][1] | boards[opp][2]));

            // bishop + 1/2 queen
            ll bishopBlocker = bishopAll[i] & allP;
            int ind2 = (bishopBlocker * bishopMagic[i]) >> (64 - 14);
            ll bishopMask = bishopMoves[i][ind2];
            bishopMask &= ~all[side];

            ret |= (bishopMask & (boards[opp][1] | boards[opp][3]));
            return ret;
        }


        inline ll otherChecks(bool side) {
            int i = kingSq[side];
            int opp = side ^ 1;
            ll ret = 0;

            // knight
            ret |= (knightAtk[i] & boards[opp][4]);

            // pawn
            ret |= (side == 0 && bPawnAtk[i] & boards[opp][5]);
            ret |= (side == 1 && wPawnAtk[i] & boards[opp][5]);

            return ret;
        }

        inline ll slidingAtkMask(int i, bool side) {
            int opp = side ^ 1;
            int ksq = kingSq[opp];
            int rq = i >> 3;
            int fq = i & 7;
            int rk = ksq >> 3;
            int fk = ksq & 7;

            int d  = ((rk > rq) - (rk < rq)) * 8 + (fk > fq) - (fk < fq); 

            ll blocker = kingAtk[i];
            blocker &= ~(1ULL << (i - d));
            blocker |= (1ULL << ksq);

            ll rookBlock = (rookAll[i] & blocker);
            ll rookInd = (rookBlock * rookMagic[i]) >> (64 - 14);
            ll rookMask = rookMoves[i][rookInd] & ~blocker;

            ll bishopBlock = (bishopAll[i] & blocker);
            ll bishopInd = (bishopBlock * bishopMagic[i]) >> (64 - 14);
            ll bishopMask = bishopMoves[i][bishopInd] & ~blocker;

            return rookMask | bishopMask;
        }

        inline int genMoves(bool side, Move* moves, int appendInd=0) {

            ll all[] = {whiteP(), blackP()};
            ll allP = all[0] | all[1];
            int opp = side ^ 1;
            ll slidingC = slidingChecks(side);
            ll otherC = otherChecks(side);
            int checkCnt = cnt(slidingC | otherC);

            // king moves
            int i = kingSq[side];
            ll kMask = kingAtk[i] & ~all[side];
            while (kMask) {
                int j = lsb(kMask);
                moves[appendInd++] = Move(i, j, 0, at(j, opp));
                kMask &= kMask - 1;
            }

            // only king moves legal during double check
            if (checkCnt > 1) return appendInd;

            // can only castle if not in check
            if (checkCnt == 0) {
                if (kCastle[side] && on(boards[side][2], i + 3)) {
                    if (!attacked(i + 1, side) && !attacked(i + 2, side) && !on(allP, i + 1) && !on(allP, i + 2)) {
                        Move m(i, i + 2, 0, -1);
                        m.castleK = true;
                        moves[appendInd++] = m;
                    }
                }
                if (qCastle[side] && on(boards[side][2], i - 4)) {
                    if (!attacked(i - 1, side) && !attacked(i - 2, side) && !on(allP, i - 1) && !on(allP, i - 2) && !on(allP, i - 3)) {
                        Move m(i, i - 2, 0, -1);
                        m.castleQ = true;
                        moves[appendInd++] = m;
                    }
                }
            }

            // ll slidingCheckMoves = -1;
            // ll otherCheckMoves = -1;
            // if (slidingC) slidingCheckMoves = slidingAtkMask(lsb(slidingC), side);
            // if (otherC) otherCheckMoves = otherC;

            // queen moves
            ll queenMask = boards[side][1];
            while (queenMask) {
                int i = lsb(queenMask);
                ll blocker1 = rookAll[i] & allP;
                ll blocker2 = bishopAll[i] & allP;
                int ind1 = (blocker1 * rookMagic[i]) >> (64 - 14);
                int ind2 = (blocker2 * bishopMagic[i]) >> (64 - 14);
                ll movesMask = rookMoves[i][ind1] | bishopMoves[i][ind2];
                movesMask &= ~all[side];
                // movesMask &= slidingCheckMoves;
                // movesMask &= otherCheckMoves;

                while (movesMask) {
                    int j = lsb(movesMask);
                    moves[appendInd++] = Move(i, j, 1, at(j, opp));
                    movesMask &= movesMask - 1;
                }

                queenMask &= queenMask - 1;
            } 

            // rook moves
            ll rookMask = boards[side][2];
            while (rookMask) {
                int i = lsb(rookMask);
                ll blocker1 = rookAll[i] & allP;
                int ind = (blocker1 * rookMagic[i]) >> (64 - 14);
                ll movesMask = rookMoves[i][ind];
                movesMask &= ~all[side];
                // movesMask &= slidingCheckMoves;
                // movesMask &= otherCheckMoves;

                while (movesMask) {
                    int j = lsb(movesMask);
                    moves[appendInd++] = Move(i, j, 2, at(j, opp));
                    movesMask &= movesMask - 1;
                }

                rookMask &= rookMask - 1;
            }

            // bishop moves
            ll bishopMask = boards[side][3];
            while (bishopMask) {
                int i = lsb(bishopMask);
                ll blocker2 = bishopAll[i] & allP;
                int ind = (blocker2 * bishopMagic[i]) >> (64 - 14);
                ll movesMask = bishopMoves[i][ind];
                movesMask &= ~all[side];
                // movesMask &= slidingCheckMoves;
                // movesMask &= otherCheckMoves;

                while (movesMask) {
                    int j = lsb(movesMask);
                    moves[appendInd++] = Move(i, j, 3, at(j, opp));
                    movesMask &= movesMask - 1;
                }

                bishopMask &= bishopMask - 1;
            }

            // knight moves
            ll knightMask = boards[side][4];
            while (knightMask) {
                int i = lsb(knightMask);
                ll nMask = knightAtk[i] & ~all[side];
                // nMask &= slidingCheckMoves;
                // nMask &= otherCheckMoves;
                while (nMask) {
                    int j = lsb(nMask);
                    moves[appendInd++] = Move(i, j, 4, at(j, opp));
                    nMask &= nMask - 1;
                }

                knightMask &= knightMask - 1;
            }

            auto pawnPush = [&] (bool side, Move &m) {
                if ((side == 1 && m.to >= 8) || side == 0 && m.to <= 55) {
                    moves[appendInd++] = m;
                    return;
                }
                
                m.promo = 1;
                Move m2 = Move(m); m2.promo = 2;
                Move m3 = Move(m); m3.promo = 3;
                Move m4 = Move(m); m4.promo = 4;
                moves[appendInd++] = m;
                moves[appendInd++] = m2;
                moves[appendInd++] = m3;
                moves[appendInd++] = m4;
            };

            // pawn moves
            ll pawnMask = boards[side][5];
            while (pawnMask) {
                int i = lsb(pawnMask);
                if (side == 0) {
                    // one square up
                    if (i + 8 < 64 && !on(allP, i + 8)) {
                        Move m(i, i + 8, 5, -1);
                        pawnPush(side, m);
                    }

                    // take left
                    if (i + 7 < 64 && (i & 7) != 0 && on(all[opp], i + 7)) {
                        Move m(i, i + 7, 5, at(i + 7, opp));
                        pawnPush(side, m);
                    }

                    // take right
                    if (i + 9 < 64 && (i & 7) != 7 && on(all[opp], i + 9)) {
                        Move m(i, i + 9, 5, at(i + 9, opp));
                        pawnPush(side, m);
                    }

                    // two squares up
                    if (i >= 8 && i <= 15) {
                        if (!on(allP, i + 8) && !on(allP, i + 16)) {
                            Move m(i, i + 16, 5, -1);
                            m.pawnTwo = 1;
                            moves[appendInd++] = m;
                        }
                    }

                    // enp left
                    if (i >= 33 && i <= 39 && i - 1 == pawnTwo + 32) {
                        Move m(i, i + 7, 5, -1);
                        m.enp = 1;
                        moves[appendInd++] = m;
                    }

                    // enp right
                    if (i >= 32 && i <= 38 && i + 1 == pawnTwo + 32) {
                        Move m(i, i + 9, 5, -1);
                        m.enp = 1;
                        moves[appendInd++] = m;
                    }
                }
                else {
                    // one square up
                    if (i - 8 >= 0 && !on(allP, i - 8)) {
                        Move m(i, i - 8, 5, -1);
                        pawnPush(side, m);
                    }

                    // take left (from blacks perspective)
                    if (i - 7 >= 0 && (i & 7) != 7 && on(all[opp], i - 7)) {
                        Move m(i, i - 7, 5, at(i - 7, opp));
                        pawnPush(side, m);
                    }

                    // take right
                    if (i - 9 >= 0 && (i & 7) != 0 && on(all[opp], i - 9)) {
                        Move m(i, i - 9, 5, at(i - 9, opp));
                        pawnPush(side, m);
                    }

                    // two squares up
                    if (i >= 48 && i <= 55) {
                        if (!on(allP, i - 8) && !on(allP, i - 16)) {
                            Move m(i, i - 16, 5, -1);
                            m.pawnTwo = 1;
                            moves[appendInd++] = m;
                        }
                    }

                    // enp left
                    if (i >= 24 && i <= 30 && i + 1 == 24 + pawnTwo) {
                        Move m(i, i - 7, 5, -1);
                        m.enp = 1;
                        moves[appendInd++] = m;
                    }

                    // enp right
                    if (i >= 25 && i <= 31 && i - 1 == 24 + pawnTwo) {
                        Move m(i, i - 9, 5, -1);
                        m.enp = 1;
                        moves[appendInd++] = m;
                    }
                }

                pawnMask &= pawnMask - 1;
            }

            return appendInd;
        }

        inline bool makeMove(Move& m) {
            m.oldKCastle = kCastle[turn];
            m.oldQCastle = qCastle[turn];
            m.oldHalfMoves = halfMoves;
            m.oldPawnTwo = pawnTwo;

            pawnTwo = -1; // clean out for next round of enp

            boards[turn][m.board1] ^= 1ULL << m.from;
            boards[turn][m.board1] |= 1ULL << m.to;

            if (m.board2 != -1) {
                boards[turn ^ 1][m.board2] ^= 1ULL << m.to;
            }
            
            if (m.board1 == 0) {
                kingSq[turn] = m.to;
                kCastle[turn] = 0;
                qCastle[turn] = 0;
            }

            if (m.board1 == 2) {
                if (turn == 0 && m.from == 7)  kCastle[0] = 0;
                if (turn == 0 && m.from == 0)  qCastle[0] = 0;
                if (turn == 1 && m.from == 63) kCastle[1] = 0;
                if (turn == 1 && m.from == 56) qCastle[1] = 0;
            }

            if (m.pawnTwo) {
                pawnTwo = m.to & 7;
            }

            if (m.enp) {
                if (turn == 0) {
                    boards[1][5] ^= 1ULL << (m.to - 8);
                }
                else {
                    boards[0][5] ^= 1ULL << (m.to + 8);
                }
            }


            if (m.castleK) {
                kCastle[turn] = 0;
                boards[turn][2] ^= 1ULL << (m.to + 1);
                boards[turn][2] |= 1ULL << (m.to - 1);
            }
            else if (m.castleQ) {
                qCastle[turn] = 0;
                boards[turn][2] ^= 1ULL << (m.to - 2);
                boards[turn][2] |= 1ULL << (m.to + 1);
            }

            if (m.promo) {
                boards[turn][5] ^= 1ULL << m.to;
                boards[turn][m.promo] ^= 1ULL << m.to;
            }

            if (m.board2 != -1 || m.board1 == 5) {
                halfMoves = 0;
            }
            else {
                halfMoves++;
            }
            
            turn ^= 1;

            if (attacked(kingSq[turn ^ 1], turn ^ 1)) {
                // ILLEGAL MOVE
                unmakeMove(m);
                return 0;
            }

            return 1;
        }

        inline void unmakeMove(Move& m) {
            turn ^= 1;
            halfMoves = m.oldHalfMoves;
            kCastle[turn] = m.oldKCastle;
            qCastle[turn] = m.oldQCastle;
            pawnTwo = m.oldPawnTwo;

            if (m.board1 == 0) {
                kingSq[turn] = m.from;
            }
            
            if (m.promo) {
                boards[turn][m.promo] ^= 1ULL << m.to;
                boards[turn][5] ^= 1ULL << m.from;
            }
            else {
                boards[turn][m.board1] ^= 1ULL << m.to;
                boards[turn][m.board1] |= 1ULL << m.from;
            }

            if (m.board2 != -1) {
                boards[turn ^ 1][m.board2] ^= 1ULL << m.to;
            }

            if (m.enp) {
                if (turn == 0) {
                    boards[1][5] |= 1ULL << (m.to - 8);
                }
                else {
                    boards[0][5] |= 1ULL << (m.to + 8);
                }
            }

            if (m.castleK) {
                boards[turn][2] ^= 1ULL << (m.to - 1);
                boards[turn][2] |= 1ULL << (m.to + 1);
            }
            else if (m.castleQ) {
                boards[turn][2] ^= 1ULL << (m.to + 1);
                boards[turn][2] |= 1ULL << (m.to - 2);
            }
        }

        inline bool isLegal(Move& m) {
            if (!makeMove(m)) return 0;
            unmakeMove(m);
            return 1;
        }

        // TODO
        inline string getFEN() {
            string fen = "";

            for (int i = 56; i >= 0; i -= 8) {
                int empty = 0;
                for (int j = 0; j < 8; j++) {
                    int whitePiece = at(i + j, 0);
                    int blackPiece = at(i + j, 1);

                    if (whitePiece != -1) {
                        if (empty != 0) fen += to_string(empty);
                        fen += toupper(numPieceChar[whitePiece]);
                        empty = 0;
                    }
                    else if (blackPiece != -1) {
                        if (empty != 0) fen += to_string(empty);
                        fen += numPieceChar[blackPiece];
                        empty = 0;
                    }
                    else {
                        empty++;
                    }
                }
                if (empty != 0) fen += to_string(empty);
                if (i != 0)fen += "/";
            }
            fen += " ";
            
            if (turn == 0) fen += "w";
            else fen += "b";
            fen += " ";

            if (kCastle[0]) fen += "K";
            if (qCastle[0]) fen += "Q";
            if (kCastle[1]) fen += "k";
            if (qCastle[1]) fen += "q";
            fen += " ";

            if (pawnTwo != -1) {
                fen += 'a' + pawnTwo;
                if (turn == 0) fen += "3";
                else fen += "6";
            }
            else {
                fen += "-";
            }
            fen += " ";

            fen += to_string(halfMoves);
            fen += " ";

            fen += "1";
            return fen;
        }
};

inline Board b;

#endif