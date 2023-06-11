#include <bits/stdc++.h>
#include "TicTacToe.h"
#define COMPUTER_MOVE 'X'
#define HUMAN_MOVE 'O'

using namespace std;

ticTacToe::ticTacToe()
{
    for (int i = 0; i < SIZE; i++)
    {
        string temp;
        for (int j = 0; j < SIZE; j++)
            temp.push_back('-');

        grid.push_back(temp);
        for (int j = 0; j < SIZE; j++)
            possibleMoves.insert(make_pair(i, j));
    }
}

void ticTacToe::play(pair<int, int> firstM)
{
    playMove(move);

    while (possibleMoves.size())
    {
        cin >> humMove.first >> humMove.second;
        grid[humMove.first][humMove.second] = HUMAN_MOVE;
        possibleMoves.erase(humMove);

        bool foundWin = false;
        pair<int, int> winMove, drawMove;

        for (auto i : possibleMoves)
        {
            auto temp = grid;
            temp[i.first][i.second] = 'X';

            int result = bestMove('O', temp);

            if (result == 1)
            {
                winMove = i;
                foundWin = true;
                break;
            }

            else if (result == 0)
                drawMove = i;
        }

        if (foundWin)
            playMove(winMove);

        else
            playMove(drawMove);

        if (terminal(grid, possibleMoves) != -2)
        {
            if (foundWin)
                cout << "\t\t\tCOMPUTER WINS!!" << endl;
            else
                cout << "\t\t\tIt's a Draw..." << endl;

            return;
        }
    }
}

void ticTacToe::playMove(pair<int, int> move)
{
    int x = move.first;
    int y = move.second;

    grid[x][y] = COMPUTER_MOVE;
    possibleMoves.erase(move);

    for (int i = 0; i < SIZE; i++)
    {
        cout << "\t\t\t";
        for (int j = 0; j < SIZE; j++)
            cout << grid[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

int ticTacToe::terminal(vector<string> tempGrid, set<pair<int, int>> tempMoves) const
{
    for (int i = 0; i < SIZE; i++)
    {
        map<char, int> count;

        for (int j = 0; j < SIZE; j++)
            count[tempGrid[i][j]]++;

        if (count['X'] == SIZE)
            return 1;
        else if (count['O'] == SIZE)
            return -1;
    }

    for (int i = 0; i < SIZE; i++)
    {
        map<char, int> count;

        for (int j = 0; j < SIZE; j++)
            count[tempGrid[j][i]]++;

        if (count['X'] == SIZE)
            return 1;
        else if (count['O'] == SIZE)
            return -1;
    }

    map<char, int> count;
    for (int i = 0; i < SIZE; i++)
        count[tempGrid[i][i]]++;

    if (count['X'] == SIZE)
        return 1;
    else if (count['O'] == SIZE)
        return -1;

    count['X'] = 0;
    count['O'] = 0;

    for (int i = 0; i < SIZE; i++)
        count[tempGrid[i][SIZE - i - 1]]++;

    if (count['X'] == SIZE)
        return 1;
    else if (count['O'] == SIZE)
        return -1;

    count['X'] = 0;
    count['O'] = 0;

    if (tempMoves.empty())
        return 0;

    return -2;
}

int ticTacToe::bestMove(char player, vector<string> grid)
{
    set<pair<int, int>> tempMoves = getPossibleMoves(grid);
    int flag = terminal(grid, tempMoves);

    if (flag != -2)
        return flag;

    int optimalResult = 0;
    if (player == 'X')
    {
        optimalResult = -1;
        for (auto i : tempMoves)
        {
            auto temp = grid;
            temp[i.first][i.second] = 'X';

            int result = bestMove('O', temp);
            optimalResult = max(optimalResult, result);
        }
    }

    else if (player == 'O')
    {
        optimalResult = 1;
        for (auto i : tempMoves)
        {
            auto temp = grid;
            temp[i.first][i.second] = 'O';

            int result = bestMove('X', temp);
            optimalResult = min(optimalResult, result);
        }
    }

    return optimalResult;
}

set<pair<int, int>> ticTacToe::getPossibleMoves(vector<string> grid) const
{
    set<pair<int, int>> poss;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == '-')
                poss.insert(make_pair(i, j));
        }
    }

    return poss;
}
