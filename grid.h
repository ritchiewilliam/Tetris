#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H
#include "global.h"
#include "block.h"

const int GRID_Y = 20;
const int GRID_X = 10;

class Grid {
public:
    Grid();
    int placeBlock();
    int moveBlock(unsigned int);
    void clearRows(point *);
    void getGrid(int **);
    void quit();

//    int getScore();

private:
    int **grid;
    Block * block;
    bool blockSaved = false;
    Block * savedBlock;
//    int score;

    void shiftRows(int[blockSize], int);
    int differentType(int);
    void saveBlock();
};


#endif //TETRIS_GRID_H
