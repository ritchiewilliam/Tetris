#ifndef TETRIS_GRID_H
#define TETRIS_GRID_H
#include "global.h"
#include "block.h"
#include <deque>
#include <SDL2/SDL_image.h>	

class Grid {
public:
    Grid();
    bool placeBlock();
    bool moveBlock(unsigned int);
    void clearRows(std::array <point, blockSize>);
    void getGrid(int (&dest)[GRID_X][GRID_Y]);
    int getSaved();
    const std::deque<int> getNext();
    
//    int getScore();

private:
    int grid[GRID_X][GRID_Y];

    std::deque <int> nextBlocks;
    Block block;
    bool blockSaved = false;
    Block savedBlock = Block(7);
//    Texture * textures;
//    int score;

    void shiftRows(const int[blockSize], int);
    int differentType(int);

    int newBlock();
    void saveBlock();
};


#endif //TETRIS_GRID_H
