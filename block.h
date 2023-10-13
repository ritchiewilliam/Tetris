#ifndef TETRIS_BLOCK_H
#define TETRIS_BLOCK_H

enum Direction {UP = 111, DOWN = 116, LEFT = 113, RIGHT = 114, SPACE = 65};

typedef struct{
    int x;
    int y;
} point;

const int typeNums = 7;
const int blockSize = 4;

class Block {
public:
    Block();
    Block(int);
    point * getPositions();
    int rotate(unsigned int **);
    int translate(unsigned int **, Direction);
    unsigned int getColor();
    int getType();
private:
    int type;
    point position[4];
    point pivot;

    const point TEMPLATES[7][4] { //Note: PIVOT IS ALWAYS FIRST VALUE
        {{5,1}, {5,0}, {5,2}, {5,3}}, //I
        {{5,1}, {5,0}, {6,0}, {6,1}}, //SQUARE
        {{5,1}, {5,0}, {4,1}, {6,1}}, //T
        {{5,1}, {5,0}, {5,2}, {6,2}}, //L
        {{5,1}, {5,0}, {5,2}, {4,2}}, //J
        {{5,1}, {5,0}, {4,1}, {6,0}}, //S
        {{5,1}, {5,0}, {6,1}, {4,0}}  //Z
    };

    const unsigned int COLORS[7] {
        0x00FFFF, //I - cyan
        0xFFFF00, //SQUARE - yellow
        0x800080, //T - purple
        0xFF7F00, //L - orange
        0x0000FF, //J - blue
        0x00FF00, //S - green
        0xFF0000  //Z - red
    };

};


#endif //TETRIS_BLOCK_H
