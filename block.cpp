#include <cstdlib>
#include <cstring>
#include "block.h"


Block::Block() {
    type = rand()% typeNums;

//    std::memcpy(position, TEMPLATES[type], sizeof(point) * blockSize);
    for(int i = 0; i < blockSize; i++) {
        position[i].x = TEMPLATES[type][i].x;
        position[i].y = TEMPLATES[type][i].y;
    }

    pivot = position[0];
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
    for(int i = 0; i < blockSize; i++) {
        position[i].x = TEMPLATES[type][i].x;
        position[i].y = TEMPLATES[type][i].y;
    }
    pivot = position[0];
}

int Block::rotate(int ** grid) {
    point temp[blockSize];
    std::memcpy(temp, position, sizeof(point) *  blockSize);
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

            memcpy(position, temp, sizeof(point) * blockSize);
            return 0;
        }
    }
    return 1;
}

int Block::translate(int ** grid, Direction d) {
    point temp[blockSize];
    std::memcpy(temp, position, sizeof(point) * blockSize);
    for (point &i: position) {
        i.x += (d == RIGHT) - (d == LEFT);
        i.y += (d == DOWN);
        if (i.x < 0 || i.y > 19 || i.x > 9 || (grid[i.x][i.y] > -1)) {
            memcpy(position, temp, sizeof(point) * blockSize);
            return 0;
        }
    }
    pivot = position[0];
    return 1;
}

point * Block::getPositions() {
    auto *rtn = new point[blockSize];
    memcpy(rtn, position, sizeof(point) * blockSize);

    return rtn;
}

void Block::resetPositions() {
    memcpy(position, TEMPLATES[type], sizeof(point) * blockSize);
}

//unsigned int Block::getColor(){
//    return COLORS[type];
//}

int Block::getType(){
    return type;
}
