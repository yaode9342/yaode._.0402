#include "MazeGame.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout << "操作指示 (w -上, a -左, s -下, d -右): " << endl;

    MazeGame game;
    game.play();

    return 0;
}
