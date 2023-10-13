#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H
#include "block.h"

const int GRID_Y = 20;
const int GRID_X = 10;

class Grid {
public:
    Grid();
    int placeBlock();
    int moveBlock(unsigned int);
    void clearRows(point *);
    void getGrid(unsigned int **);
//    int getScore();

private:
    unsigned int **grid;
    Block * block;
//    int score;

    void shiftRows(int[blockSize], int n);
};


#endif //TETRIS_GRID_H
