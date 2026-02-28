#ifndef ROOM_H
#define ROOM_H

#include "constants.h"
#include "cell.h"

#include <vector>

class Room {
    std::vector<std::vector<Cell>> board;
public:
    Room();
};

#endif