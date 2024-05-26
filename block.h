#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include "global.h"
#include <iterator>
#include <array>
//enum Direction {UP = 111, DOWN = 116, LEFT = 113, RIGHT = 114, SPACE = 65, SAVE = 54};

class Block {
public:
    Block();
    Block(int);

    std::array<point, blockSize> getPositions();
    void resetBlock();
    void resetPositions();
    bool rotate(const int (&grid)[GRID_X][GRID_Y]);
    bool translate(const int (&grid)[GRID_X][GRID_Y], Direction);
//    unsigned int getColor();
    int getType();

private:
    int type;
    std::array <point, blockSize> position;
    point pivot;
};


#endif //TETRIS_BLOCK_H
