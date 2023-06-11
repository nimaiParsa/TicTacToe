#include <bits/stdc++.h>
#include "TicTacToe.h"

using namespace std;

int main()
{
    ticTacToe gameA;
    
    pair<int, int> move = make_pair(0, 0);
    // pair<int, int> move = make_pair(1, 1);

    gameA.play(move);

    return 0;
}