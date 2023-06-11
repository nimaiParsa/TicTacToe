#ifndef GAME
#define GAME

#include <bits/stdc++.h>
#define SIZE 3

using namespace std;

class ticTacToe
{
public:
    explicit ticTacToe();
    void play(pair<int, int>);

private:
    vector<string> grid;
    pair<int, int> humMove, move;
    set<pair<int, int>> possibleMoves;
    
    int bestMove(char, vector<string>);
    void playMove(pair<int, int>);
    int terminal(vector<string>, set<pair<int, int>>) const;
    set<pair<int, int>> getPossibleMoves(vector<string>) const;
};

#endif