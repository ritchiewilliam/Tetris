#include <cstdlib>
#include <cstring>
#include "block.h"


Block::Block() {
    resetBlock();
}

// Block::Block(int notType) {
//     srand(time(nullptr));
//     type = notType;
//     while(type == notType) {
//         type = rand() % typeNums;
//     }
//     std::memcpy(position, TEMPLATES[type], sizeof(point) * typeNums);
//     pivot = position[0];
// }

Block::Block(int type) {
    this->type = type;
//    std::memcpy(position, TEMPLATES[type], sizeof(point) * blockSize);
    if(type < 7) {
	    /*for(int i = 0; i < blockSize; i++) {
		position[i].x = TEMPLATES[type][i].x;
		position[i].y = TEMPLATES[type][i].y;
	    }*/
	    std::copy(std::begin(TEMPLATES[type]), std::end(TEMPLATES[type]), std::begin(position));
    }
    pivot = position[0];
}

/*
void Block::operator=(const Block& block) {
    type = block.type;
    
    for(int i = 0; i < blockSize; i++) {
	position[i] = block.position[i];
    }

    pivot = position[0];
}*/


bool Block::rotate(const int (&grid)[GRID_X][GRID_Y]) {
    point temp[blockSize];

    std::copy(std::begin(position), std::end(position), std::begin(temp));
    //std::memcpy(temp, position, sizeof(point) *  blockSize);


    for(point &i:position) {
        //Use pivot as origin
        i.x -= pivot.x;
        i.y -= pivot.y;

        //Rotate
        int x = i.x; //temp to store original value for y transformation
        i.x = i.y * -1;
        i.y = x;

        i.x += pivot.x;
        i.y += pivot.y;

        if (i.x < 0 || i.y > 19 || i.x > 9 || (grid[i.x][i.y] > -1)) {
	    std::copy(std::begin(temp), std::end(temp), std::begin(position));
            //memcpy(position, temp, sizeof(point) * blockSize);
            return false;
        }
    }
    return true;
}

bool Block::translate(const int (&grid)[GRID_X][GRID_Y], Direction d) {
    point temp[blockSize];

    std::copy(std::begin(position), std::end(position), std::begin(temp));
    //std::memcpy(temp, position, sizeof(point) * blockSize);
    for (point &i: position) {
        i.x += (d == RIGHT) - (d == LEFT);
        i.y += (d == DOWN);
        if (i.x < 0 || i.y > 19 || i.x > 9 || (grid[i.x][i.y] > -1)) {
	    std::copy(std::begin(temp), std::end(temp), std::begin(position));
            //memcpy(position, temp, sizeof(point) * blockSize);
            return false;
        }
    }
    pivot = position[0];
    return true;
}

std::array <point, blockSize> Block::getPositions() {
    std::array <point, blockSize> rtn;
    std::copy(std::begin(position), std::end(position), std::begin(rtn));
    return rtn;
}

void Block::resetBlock() {
    type = rand() % typeNums;

//    std::memcpy(position, TEMPLATES[type], sizeof(point) * blockSize);
    std::copy(std::begin(TEMPLATES[type]), std::end(TEMPLATES[type]), std::begin(position));

    pivot = position[0];
}

void Block::resetPositions() {
    //memcpy(position, TEMPLATES[type], sizeof(point) * blockSize);
    //std::copy(TEMPLATES[type], TEMPLATES[type] + sizeof(point) * blockSize, position.begin());
    std::copy(std::begin(TEMPLATES[type]), std::end(TEMPLATES[type]), std::begin(position));
    pivot = position[0];
}

//unsigned int Block::getColor(){
//    return COLORS[type];
//}

int Block::getType(){
    return type;
}
