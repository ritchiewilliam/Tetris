#include <iostream>
#include <cstring>
#include "grid.h"

Grid::Grid() {
    //grid = new int *[GRID_X];
    for(int i = 0; i < GRID_X; i++) {
        //grid[i] = new int[GRID_Y];
        for(int j = 0; j < GRID_Y; j++) {
            grid[i][j] = -1;
        }
    }
    srand(time(nullptr));

    int prevType = block.getType();
    for(int i = 0; i < queueSize; i++) {
	nextBlocks.push_front(differentType(prevType));
	prevType = nextBlocks.front();
    }
//    score = 0;
}

bool Grid::placeBlock() {
    //Move block as far down as it can go
    while(block.translate(grid, DOWN));

    //Place block onto the grid
    std::array <point, blockSize> positions = block.getPositions();
    for(int i = 0; i < blockSize; i++) {
        grid[positions[i].x][positions[i].y] = block.getType();
    }
    clearRows(positions);

    //Create new block
    block = Block(newBlock());  //NEW BLOCK

    //Make sure nothing is in the way of the newly created block
    positions = block.getPositions();
    for(int i = 0; i < blockSize; i++) {
        if(grid[positions[i].x][positions[i].y] > 0) {
            //Notify whoever called that the game is over now
            return false;
        }
    }
    blockSaved = false; //New block so saved block can be replaced again

    return true;
}

bool Grid::moveBlock(unsigned int key) {

    switch(key) {
        case Direction::RIGHT:
        case Direction::LEFT:
        case Direction::DOWN:
            return block.translate(grid, static_cast<Direction>(key));
            break;
        case Direction::SPACE:
            placeBlock();
            break;
        case Direction::UP:
            block.rotate(grid);
            break;
        case Direction::SAVE:
            if(!blockSaved) {
                saveBlock();
                blockSaved = true; //You should only be able to save block once to prevent constant swapping
            }
            break;
    }
    return false;
}

void Grid::clearRows(std::array <point, blockSize> positions) {
/*
    for(int i = 0; i < 4; i++) {
	std::cout << '(' << positions[i].x << ',' << positions[i].y << ')' << std::endl;
    }*/
    int clearedRows[blockSize];
    for(int i = 0; i < blockSize; i++) {
        clearedRows[i] = positions[i].y;
        int temp[GRID_X];
        for(int j = 0; j < GRID_X; j++) {
            if(grid[j][positions[i].y] == -1) {
                for(int k = 0; k < j; k++) {
                    grid[k][positions[i].y] = temp[k];
                }
                clearedRows[i] = -1;
                break;
            }
            temp[j] = grid[j][positions[i].y];
            grid[j][positions[i].y] = -1;
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
    else {
        //Just do left if there is no r
        shiftRows(groupings[0], l);
    }
}

void Grid::shiftRows(const int group[blockSize], int n){
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
            sum += (grid[j][i - d] + 1);
            grid[j][i] = grid[j][i - d];
            grid[j][i - d] = -1;

        }
        if(!sum) {
            return;
        }
    }
}

void Grid::getGrid(int (&dest)[GRID_X][GRID_Y]) {
    //for (int i = 0; i < GRID_X; i++) {
    std::memcpy(dest, grid, sizeof(unsigned int) * GRID_X * GRID_Y);
    //}
    //std::copy(std::begin(grid), std::end(grid), dest);

    std::array<point, blockSize> blockPositions = block.getPositions();
    for (int i = 0; i < blockSize; i++) {
        dest[blockPositions[i].x][blockPositions[i].y] = block.getType();
    }

    std::array<point, blockSize> temp;
    std::copy(std::begin(blockPositions), std::end(blockPositions), std::begin(temp));
    //std::memcpy(temp, blockPositions, sizeof(point) * blockSize);
    int j;
    int difference = temp[0].y;
    do {
        for (j = 0; j < blockSize; j++) {
            temp[j].y++;
            if (temp[j].y > 19 || (grid[temp[j].x][temp[j].y] + 1)) {
		std::copy(std::begin(blockPositions), std::end(blockPositions), std::begin(temp));
                //memcpy(temp, blockPositions, sizeof(point) * blockSize);
                break;
            }
        }
        if(j == blockSize) {
	    std::copy(std::begin(temp), std::end(temp), std::begin(blockPositions));
            //memcpy(blockPositions, temp, sizeof(point) * blockSize);
        }
    } while (j == blockSize);

    difference = blockPositions[0].y - difference;

    int type = block.getType();

    for (int i = 0; i < blockSize; i++) {
        if(dest[blockPositions[i].x][blockPositions[i].y] != type) {
//            dest[blockPositions[i].x][blockPositions[i].y] = (color & 0xfefefe) >> 1;
            dest[blockPositions[i].x][blockPositions[i].y] = type + typeNums;
        }
        dest[blockPositions[i].x][blockPositions[i].y - difference] = type;
    }

    //delete(blockPositions);
}

int Grid::differentType(int prevType) {
    int newType = prevType;

    while(prevType == newType) {
        newType = rand() % typeNums;
    }
    return newType;
}

void Grid::saveBlock() {
    if(savedBlock.getType() != 7) {
        Block temp = Block(7);
        block.resetPositions();
        temp = block;
        block = savedBlock;
        savedBlock = temp;
    }
    else {
        block.resetPositions();
        savedBlock = block;
        block = Block(newBlock()); //NEW BLOCK
    }
}

int Grid::newBlock() {
	int blockType = nextBlocks.front();
	nextBlocks.pop_front();
	nextBlocks.push_back(differentType(nextBlocks.back()));
	return blockType;
/*
	char conv[typeNums] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
	for (Block blk : blocks) {
        	std::cout << conv[blk.getType()] << ", ";
    	}
	std::cout << std::endl;*/
}

int Grid::getSaved() {
	return savedBlock.getType();
}

const std::deque<int> Grid::getNext() {
	return nextBlocks;
}

//
//int Grid::getScore() {
//    return this->score;
//}
