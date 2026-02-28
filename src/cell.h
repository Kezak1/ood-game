#ifndef CELL_H
#define CELL_H

#include "item.h"
#include "constants.h"

#include <memory>

class Cell {
    char c;
    std::unique_ptr<Item> item;
public:
    Cell();
    Cell(Cells cc);
};

#endif