#include "tetris.h"

Board::Board() {
    // ��l�ƴѽL
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = ' ';
        }
    }
}

void Board::draw() {
    // ø�s�ѽL
    std::cout << "�z";
    for (int j = 0; j < WIDTH; j++) {
        std::cout << "�w�w";
    }
    std::cout << "�{" << std::endl;

    for (int i = 0; i < HEIGHT; i++) {
        std::cout << "�x";
        for (int j = 0; j < WIDTH; j++) {
            std::cout << " " << board[i][j];
        }
        std::cout << " �x" << std::endl;
    }

    std::cout << "�|";
    for (int j = 0; j < WIDTH; j++) {
        std::cout << "�w�w";
    }
    std::cout << "�}" << std::endl;
}

bool Board::isGameOver() {
    // �ˬd�C���O�_�����]���ݬO�_������^
    for (int j = 0; j < WIDTH; j++) {
        if (board[0][j] != ' ') {
            return true;
        }
    }
    return false;
}

void Board::clearLine(int line) {
    // �M�����w��ƪ�����æV�U���ʤW�������
    for (int i = line; i > 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = board[i - 1][j];
        }
    }
}

void Board::merge(int x, int y, char shape) {
    // �N����Ϊ��X�֨�ѽL
    board[y][x] = shape;
}

bool Board::canMerge(int x, int y) {
    // �ˬd�O�_�i�H�X�֤��
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return false;
    }
    return board[y][x] == ' ';
}

char Board::getShape(int x, int y) {
    // ���o���w��m������Ϊ�
    return board[y][x];
}


Tetromino::Tetromino() {
    // ��l�Ƥ���Ϊ��]�H�G���}�C��ܡ^
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

    // �H����ܤ@�Ӥ���Ϊ�
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = shapes[randomIndex][i][j];
        }
    }

    // ��l�Ƥ������m
    x = WIDTH / 2;
    y = 0;
}

void Tetromino::rotate() {
    // �������Ϊ��]�f�ɰw����90�ס^
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
    // �V�����ʤ��
    x--;
}

void Tetromino::moveRight() {
    // �V�k���ʤ��
    x++;
}

void Tetromino::moveDown() {
    // �V�U���ʤ��
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
    // �N����X�֨�ѽL�W
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
    // ��l�� Tetris ����
}

void Tetris::play() {
    // �C���D�j��
    while (true) {
        board.draw();

        if (board.isGameOver()) {
            std::cout << "Game Over!" << std::endl;
            break;
        }

        // �ˬd����O�_�i�H�V�U����
        if (tetromino.canMoveDown(board)) {
            tetromino.moveDown();
        }
        else {
            // �N����X�֨�ѽL�W
            tetromino.merge(board);

            // �ˬd�O�_���i�H��������
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

            // �ͦ��s�����
            tetromino = Tetromino();
        }

        // �B�z���a��J
        char input;
        std::cin >> input;
        if (input == 'a' || input == 'A') {
            // �V�����ʤ��
            while (tetromino.canMoveLeft(board)) {
                tetromino.moveLeft();
            }
        }
        else if (input == 'd' || input == 'D') {
            // �V�k���ʤ��
            while (tetromino.canMoveRight(board)) {
                tetromino.moveRight();
            }
        }
        else if (input == 's' || input == 'S') {
            // �[�t�V�U���ʤ��
            while (tetromino.canMoveDown(board)) {
                tetromino.moveDown();
            }
        }
        else if (input == 'w' || input == 'W') {
            //������
            while (tetromino.canRotate(board)) {
                tetromino.rotate();
            }
        }
}