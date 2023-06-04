#include "MazeGame.h"
using namespace std;

MazeGame::MazeGame() {
    // 初始化玩家位置
    playerRow = 1;
    playerCol = 1;

    // 设置初始关卡
    currentLevel = 1;
    setCurrentLevel(currentLevel);
}
void MazeGame::play() {
    cout << "迷宮遊戲!!!(總共有三關)" << endl;
    cout << "試著讓P走到E" << endl;
    cout << endl;

    // 三個關卡
    for (currentLevel = 1; currentLevel <= 3; currentLevel++) {
        cout << "第" << currentLevel << "關" << endl;
        setCurrentLevel(currentLevel); // 設置當前關卡
        isLevelCompleted = false; // 重製關卡完成標誌

        while (true) {
            displayMaze();

            cout << "剩餘步數: " << maxMoves - moveCount << endl;

            char move;
            cout << "輸入:";
            cin >> move;

            if (isValidMove(move)) {
                updatePlayerPosition(move);
                moveCount++;

                if (isExitReached()) {
                    cout << "你找到出口了!!" << endl;
                    isLevelCompleted = true;// 標記關卡完成
                    break;
                }

                if (moveCount >= maxMoves) {
                    cout << "步數已用完，遊戲結束!" << endl;
                    break;
                }
            }
            else {
                cout << "撞牆了" << endl;
            }
        }
        if (!isLevelCompleted) {
            cout << "您挑戰到第" << currentLevel << "關" << endl;
            break;
        }
        else {
            cout << "恭喜! 三關都過了!!" << endl;
        }
    }
    cout << "感謝遊玩!" << endl;
}
void MazeGame::setCurrentLevel(int level) {
    // 设置关卡的迷宫地图、出口位置和最大移动次数
    switch (level) {
    case 1:
        maze = {
            {'#', '#', '#', '#', '#', '#', '#'},
            {'#', 'P', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', '#', 'E', '#'},
            {'#', '#', '#', '#', '#', '#', '#'}
        };
        exitRow = 5;
        exitCol = 5;
        maxMoves = 15;
        break;
    case 2:
        maze = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };
        exitRow = 9;
        exitCol = 8;
        maxMoves = 25;
        break;
    case 3:
        maze = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
            {'#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#'},
            {'#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
            {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'E', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
        };
        exitRow = 13;
        exitCol = 13;
        maxMoves = 40;
        break;
    }
    playerRow = 1;//將位置拉回原點
    playerCol = 1;

    moveCount = 0;
}
void MazeGame::displayMaze() {
    for (int row = 0; row < maze.size(); row++) {
        for (int col = 0; col < maze[row].size(); col++) {
            if (row == playerRow && col == playerCol) {
                cout << "P ";
            }
            else {
                cout << maze[row][col] << " ";
            }
        }
        cout << endl;
    }

}

bool MazeGame::isValidMove(char move) {
    switch (move) {
    case 'w':
        return maze[playerRow - 1][playerCol] != '#';
    case 'a':
        return maze[playerRow][playerCol - 1] != '#';
    case 's':
        return maze[playerRow + 1][playerCol] != '#';
    case 'd':
        return maze[playerRow][playerCol + 1] != '#';
    default:
        return false;
    }
}
void MazeGame::updatePlayerPosition(char move) {
    maze[playerRow][playerCol] = ' ';// 清除當前位置
    switch (move) {
    case 'w':
        playerRow--;
        break;
    case 'a':
        playerCol--;
        break;
    case 's':
        playerRow++;
        break;
    case 'd':
        playerCol++;
        break;
    }
    maze[playerRow][playerCol] = 'P';// 更新玩家位置
}
bool MazeGame::isExitReached() {
    return playerRow == exitRow && playerCol == exitCol;
}
