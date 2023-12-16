#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

#include "global.h"
//enum Direction {UP = 111, DOWN = 116, LEFT = 113, RIGHT = 114, SPACE = 65, SAVE = 54};


typedef struct{
    int x;
    int y;
} point;

const int blockSize = 4;

class Block {
public:
    Block();
    Block(int);
    point * getPositions();
    void resetPositions();
    int rotate(int **);
    int translate(int **, Direction);
//    unsigned int getColor();
    int getType();
private:
    int type;
    point position[blockSize];
    point pivot;

    const point TEMPLATES[7][blockSize] { //Note: PIVOT IS ALWAYS FIRST VALUE
            {{5,1}, {5,0}, {5,2}, {5,3}}, //I
            {{5,1}, {5,0}, {6,0}, {6,1}}, //O
            {{5,1}, {5,0}, {4,1}, {6,1}}, //T
            {{5,1}, {5,0}, {5,2}, {6,2}}, //L
            {{5,1}, {5,0}, {5,2}, {4,2}}, //J
            {{5,1}, {5,0}, {4,1}, {6,0}}, //S
            {{5,1}, {5,0}, {6,1}, {4,0}}  //Z
    };
};


#endif //TETRIS_BLOCK_H
