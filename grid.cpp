#include <iostream>
#include <cstring>
#include "grid.h"

Grid::Grid() {
    grid = new unsigned int *[GRID_X];
    for(int i = 0; i < GRID_X; i++) {
        grid[i] = new unsigned int[GRID_Y];
    }

    block = new Block;
//    score = 0;
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
    int notType = block->getType();
    delete(block);

    //Create new block different from the last one
    block = new Block(notType);

    //Make sure nothing is in the way of the newly created block
    positions = block->getPositions();
    for(int i = 0; i < blockSize; i++) {
        if(grid[positions[i].x][positions[i].y] > 0) {
            delete(positions);
            //Notify whoever called that the game is over now
            return 1;
        }
    }
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
            for(adjacent = l - 1; abs(groupings[0][adjacent] - clearedRow) != 1 && adjacent > 0; adjacent--) {
                std::cout << adjacent << std::endl;
            }
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
    for(int i = 0; i < GRID_X; i++) {
        std::memcpy(dest[i], grid[i], sizeof(unsigned int) * GRID_Y);
    }
    point * blockPositions = block->getPositions();
    for(int i = 0; i < blockSize; i++) {
        dest[blockPositions[i].x][blockPositions[i].y] = block->getColor();
    }
    delete(blockPositions);
}
//
//int Grid::getScore() {
//    return this->score;
//}
