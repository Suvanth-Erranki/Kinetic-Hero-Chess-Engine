#include <iostream>
#include <vector>
#include "board.h"
#include "search.h"
#include "perft.h"
using namespace std;

string name = "Kinetic Hero";
string author = "Suvanth Erranki // susvent";

vector<string> split(string line) {
    vector<string> res;
    string curr = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            res.push_back(curr);
            curr = "";
        }
        else {
            curr += line[i];
        }
    }
    if (curr != "") {
        res.push_back(curr);
    }
    return res;
}

void run() {
    string line;
    
    idle: while (getline(cin, line)) {
        if (line == "uci") {
            cout << "id name " << name << endl;
            cout << "id author " << author << endl;
            cout << "uciok" << endl;
        }
        else if (line == "isready") {
            cout << "readyok" << endl;
        }
        else if (line == "ucinewgame") {
            b = Board();
        }
        else if (line.starts_with("position")) {
            vector<string> args = split(line);

            for (int i = 1; i < args.size(); i++) {
                if (args[i] == "moves") {
                    for (int j = i + 1; j < args.size(); j++) {
                        string moveToMake = args[j];
                        Move* moves = new Move[256];
                        int n = b.genMoves(b.turn, moves);
                        for (int k = 0; k < n; k++) {
                            if (moves[k].toString() == moveToMake) {
                                b.makeMove(moves[k]);
                                break;
                            }
                        }
                    }
                }
                else if (args[i] == "startpos") {
                    b = Board();
                }
                else if (args[i] == "fen") {
                    string fen = args[i + 1];
                    b = Board(fen);
                }
            }
        }
        else if (line.starts_with("go")) {
            int wtime = 0;
            int btime = 0;
            int winc = 0;
            int binc = 0;

            vector<string> args = split(line);
            for (int i = 1; i < args.size(); i++) {
                if (args[i] == "wtime") {
                    wtime = stoi(args[i + 1]);
                    i++;
                }
                else if (args[i] == "btime") {
                    btime = stoi(args[i + 1]);
                    i++;
                }
                else if (args[i] == "winc") {
                    winc = stoi(args[i + 1]);
                    i++;
                }
                else if (args[i] == "binc") {
                    binc = stoi(args[i + 1]);
                    i++;
                }
                else if (args[i] == "movetime") {
                    int time = stoi(args[i + 1]);
                    i++;
                    Move m = search(time);
                    cout << "bestmove " << m.toString() << endl;
                    goto idle;
                }
                else if (args[i] == "perft") {
                    int depth = stoi(args[i + 1]);
                    perft(depth);
                    goto idle;
                }
            }

            Move m = search(wtime, btime, winc, binc);
            cout << "bestmove " << m.toString() << endl;
        }
        else if (line == "quit") {
            break;
        }
    }
}

int main() {
    run();
    return 0;
}
