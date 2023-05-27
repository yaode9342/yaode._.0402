#include "tetris.h"

Board::Board() {
    // 初始化棋盤
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = ' ';
        }
    }
}

void Board::draw() {
    // 繪製棋盤
    std::cout << "┌";
    for (int j = 0; j < WIDTH; j++) {
        std::cout << "──";
    }
    std::cout << "┐" << std::endl;

    for (int i = 0; i < HEIGHT; i++) {
        std::cout << "│";
        for (int j = 0; j < WIDTH; j++) {
            std::cout << " " << board[i][j];
        }
        std::cout << " │" << std::endl;
    }

    std::cout << "└";
    for (int j = 0; j < WIDTH; j++) {
        std::cout << "──";
    }
    std::cout << "┘" << std::endl;
}

bool Board::isGameOver() {
    // 檢查遊戲是否結束（頂端是否有方塊）
    for (int j = 0; j < WIDTH; j++) {
        if (board[0][j] != ' ') {
            return true;
        }
    }
    return false;
}

void Board::clearLine(int line) {
    // 清除指定行數的方塊並向下移動上面的方塊
    for (int i = line; i > 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = board[i - 1][j];
        }
    }
}

void Board::merge(int x, int y, char shape) {
    // 將方塊形狀合併到棋盤
    board[y][x] = shape;
}

bool Board::canMerge(int x, int y) {
    // 檢查是否可以合併方塊
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return false;
    }
    return board[y][x] == ' ';
}

char Board::getShape(int x, int y) {
    // 取得指定位置的方塊形狀
    return board[y][x];
}


Tetromino::Tetromino() {
    // 初始化方塊形狀（以二維陣列表示）
    char shapes[7][4][4] = {
         {
                { ' ', ' ', ' ', ' ' },
                { ' ', ' ', ' ', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', 'X', 'X', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', 'X', ' ', ' ' },
                { ' ', 'X', ' ', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', ' ', 'X', ' ' },
                { ' ', ' ', 'X', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', ' ', 'X', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', ' ', 'X', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', ' ', 'X', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', 'X', ' ', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', 'X', ' ', ' ' },
                { ' ', 'X', 'X', ' ' },
                { ' ', ' ', 'X', ' ' }
            },
            {
                { ' ', ' ', ' ', ' ' },
                { ' ', ' ', 'X', ' ' },
                { ' ', ' ', 'X', ' ' },
                { ' ', 'X', 'X', ' ' }
            }
    };

    // 隨機選擇一個方塊形狀
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = shapes[randomIndex][i][j];
        }
    }

    // 初始化方塊的位置
    x = WIDTH / 2;
    y = 0;
}

void Tetromino::rotate() {
    // 旋轉方塊形狀（逆時針旋轉90度）
    char rotatedShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotatedShape[i][j] = shape[j][3 - i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = rotatedShape[i][j];
        }
    }
}

void Tetromino::moveLeft() {
    // 向左移動方塊
    x--;
}

void Tetromino::moveRight() {
    // 向右移動方塊
    x++;
}

void Tetromino::moveDown() {
    // 向下移動方塊
    y++;
}

bool Tetromino::canRotate(Board& board) {
    char rotatedShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotatedShape[i][j] = shape[j][3 - i];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (rotatedShape[i][j] != ' ') {
                if (!board.canMerge(x + j, y + i) || board.getShape(x + j, y + i) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Tetromino::canMoveLeft(Board& board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] != ' ') {
                if (!board.canMerge(x + j - 1, y + i) || board.getShape(x + j - 1, y + i) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Tetromino::canMoveRight(Board& board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] != ' ') {
                if (!board.canMerge(x + j + 1, y + i) || board.getShape(x + j + 1, y + i) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Tetromino::canMoveDown(Board& board) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] != ' ') {
                if (!board.canMerge(x + j, y + i + 1) || board.getShape(x + j, y + i + 1) != ' ') {
                    return false;
                }
            }
        }
    }
    return true;
}

void Tetromino::merge(Board& board) {
    // 將方塊合併到棋盤上
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] != ' ') {
                board.merge(x + j, y + i, shape[i][j]);
            }
        }
    }
}

char Tetromino::getShape(int x, int y) {
    int relX = x - this->x;
    int relY = y - this->y;
    if (relX >= 0 && relX < 4 && relY >= 0 && relY < 4) {
        return shape[relY][relX];
    }
    return ' ';
}



Tetris::Tetris() {
    // 初始化 Tetris 物件
}

void Tetris::play() {
    // 遊戲主迴圈
    while (true) {
        board.draw();

        if (board.isGameOver()) {
            std::cout << "Game Over!" << std::endl;
            break;
        }

        // 檢查方塊是否可以向下移動
        if (tetromino.canMoveDown(board)) {
            tetromino.moveDown();
        }
        else {
            // 將方塊合併到棋盤上
            tetromino.merge(board);

            // 檢查是否有可以消除的行
            for (int i = 0; i < HEIGHT; i++) {
                bool lineFull = true;
                for (int j = 0; j < WIDTH; j++) {
                    if (board.getShape(j, i) == ' ') {
                        lineFull = false;
                        break;
                    }
                }
                if (lineFull) {
                    board.clearLine(i);
                }
            }

            // 生成新的方塊
            tetromino = Tetromino();
        }

        // 處理玩家輸入
        char input;
        std::cin >> input;
        if (input == 'a' || input == 'A') {
            // 向左移動方塊
            while (tetromino.canMoveLeft(board)) {
                tetromino.moveLeft();
            }
        }
        else if (input == 'd' || input == 'D') {
            // 向右移動方塊
            while (tetromino.canMoveRight(board)) {
                tetromino.moveRight();
            }
        }
        else if (input == 's' || input == 'S') {
            // 加速向下移動方塊
            while (tetromino.canMoveDown(board)) {
                tetromino.moveDown();
            }
        }
        else if (input == 'w' || input == 'W') {
            //旋轉方塊
            while (tetromino.canRotate(board)) {
                tetromino.rotate();
            }
        }
}