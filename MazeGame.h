#ifndef MAZEGAME_H
#define MAZEGAME_H
#include <iostream>
#include <vector>
using namespace std;

class MazeGame {
private:
    vector<vector<char>> maze;
    int playerRow;
    int playerCol;
    int exitRow;
    int exitCol;
    int maxMoves;
    int moveCount;
    int currentLevel;
    bool isLevelCompleted;

public:
    MazeGame();

    void play();

private:
    void setCurrentLevel(int level);
    void displayMaze();
    bool isValidMove(char move);
    void updatePlayerPosition(char move);
    bool isExitReached();
};

#endif
