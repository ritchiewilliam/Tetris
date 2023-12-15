#include <iostream>
#include <cstring>
#include "grid.h"

Grid::Grid() {
    grid = new unsigned int *[GRID_X];
    for(int i = 0; i < GRID_X; i++) {
        grid[i] = new unsigned int[GRID_Y];
    }
    srand(time(nullptr));

    block = new Block(rand() % typeNums);
    savedBlock = nullptr;
//    score = 0;
}

void Grid::quit(){
    for(int i = 0; i < GRID_X; i++) {
        delete(grid[i]);
    }
    delete(grid);
    delete(block);
    delete(savedBlock);
}

int Grid::placeBlock() {
    //Move block as far down as it can go
    while(block->translate(grid, DOWN));

    //Place block onto the grid
    point * positions = block->getPositions();
    for(int i = 0; i < blockSize; i++) {
        grid[positions[i].x][positions[i].y] = block->getColor();
    }
    clearRows(positions);
    delete(positions);

    //Store type for next initialization and get rid of old block
    int prevType = block->getType();

    delete(block);

    //Create new block different from the last one
    block = new Block(differentType(prevType));

    //Make sure nothing is in the way of the newly created block
    positions = block->getPositions();
    for(int i = 0; i < blockSize; i++) {
        if(grid[positions[i].x][positions[i].y] > 0) {
            delete(positions);
            //Notify whoever called that the game is over now
            return 1;
        }
    }

    blockSaved = false; //New block so saved block can be replaced again

    delete(positions);
    return 0;
}

int Grid::moveBlock(unsigned int key) {

    switch(key) {
        case Direction::RIGHT:
        case Direction::LEFT:
        case Direction::DOWN:
            return block->translate(grid, static_cast<Direction>(key));
            break;
        case Direction::SPACE:
            placeBlock();
            break;
        case Direction::UP:
            block->rotate(grid);
            break;
        case Direction::SAVE:
            if(!blockSaved) {
                saveBlock();
                blockSaved = true; //You should only be able to save block once to prevent constant swapping
            }
        break;
    }
    return 0;
}

void Grid::clearRows(point * positions) {
    int clearedRows[blockSize];
    for(int i = 0; i < blockSize; i++) {
        clearedRows[i] = positions[i].y;
        unsigned int temp[GRID_X];
        for(int j = 0; j < GRID_X; j++) {
            if(grid[j][positions[i].y] == 0) {
                for(int k = 0; k < j; k++) {
                    grid[k][positions[i].y] = temp[k];
                }
                clearedRows[i] = -1;
                break;
            }
            temp[j] = grid[j][positions[i].y];
            grid[j][positions[i].y] = 0;
        }
    }

    int l = 0;
    int r = 0;
    int groupings[2][blockSize];

    for(int clearedRow : clearedRows) {
        if(clearedRow != -1) {
            int adjacent;
            for(adjacent = l - 1; abs(groupings[0][adjacent] - clearedRow) != 1 && adjacent > 0; adjacent--);

            if (!l || abs(groupings[0][adjacent] - clearedRow) == 1) {
                groupings[0][l] = clearedRow;
                l++;
            }
            else {
                groupings[1][r] = clearedRow;
                r++;
            }
        }
    }
    if(!l) {
        return;
    }
    if(r > 0) {
        int order = groupings[0][0] > groupings[1][0];
        int n = r * order + l * (!order);
        //SMALLER GOES FIRST
        shiftRows(groupings[order], n);
        //Shouldn't be equal, I know if wouldn't cover all cases but it should never be the case
        n = l * order + r * (!order);
        shiftRows(groupings[!order], n);
    }
    else{
        //Just do left if there is no r
        shiftRows(groupings[0], l);
    }
    return;
}

void Grid::shiftRows(int group[blockSize], int n){
    int max = -1;
    int min = GRID_Y;
    for(int i = 0; i < n; i++) {
        max = group[i] * (max < group[i]) + max * (max >= group[i]);
        min = group[i] * (min > group[i]) + min * (min <= group[i]);
    }

    int d = max - min + 1;

    for(int i = max; i >= 0; i--) {
        unsigned int sum = 0;
        for(int j = 0; j < GRID_X; j++) {
            sum += grid[j][i - d];
            grid[j][i] = grid[j][i - d];
            grid[j][i - d] = 0;

        }
        if(!sum) {
            return;
        }
    }
}

void Grid::getGrid(unsigned int ** dest) {
    for (int i = 0; i < GRID_X; i++) {
        std::memcpy(dest[i], grid[i], sizeof(unsigned int) * GRID_Y);
    }
    point *blockPositions = block->getPositions();
    for (int i = 0; i < blockSize; i++) {
        dest[blockPositions[i].x][blockPositions[i].y] = block->getColor();
    }
    point temp[blockSize];
    std::memcpy(temp, blockPositions, sizeof(point) * blockSize);
    int j;
    int difference = temp[0].y;
    do {
        for (j = 0; j < blockSize; j++) {
            temp[j].y++;
            if (temp[j].y > 19 || grid[temp[j].x][temp[j].y]) {
                memcpy(temp, blockPositions, sizeof(point) * blockSize);
                break;
            }
        }
        if(j == blockSize) {
            memcpy(blockPositions, temp, sizeof(point) * blockSize);
        }
    } while (j == blockSize);

    difference = blockPositions[0].y - difference;

    unsigned int color = block->getColor();

    for (int i = 0; i < blockSize; i++) {
        if(dest[blockPositions[i].x][blockPositions[i].y] != color) {
            dest[blockPositions[i].x][blockPositions[i].y] = (color & 0xfefefe) >> 1;
        }
        dest[blockPositions[i].x][blockPositions[i].y - difference] = color;
    }

    delete(blockPositions);
}

int Grid::differentType(int prevType) {
    int newType = prevType;

    while(prevType == newType) {
        newType = rand() % typeNums;
    }
    return newType;
}

void Grid::saveBlock() {
    if(savedBlock != nullptr) {
        Block * temp;
        block->resetPositions();
        temp = block;
        block = savedBlock;
        savedBlock = temp;
    }
    else {
        block->resetPositions();
        savedBlock = block;
        block = new Block(differentType(savedBlock->getType()));
    }
}
//
//int Grid::getScore() {
//    return this->score;
//}
