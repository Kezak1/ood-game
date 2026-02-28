#ifndef CELL_H
#define CELL_H

#include "item.h"
#include "constants.h"

#include <memory>

class Cell {
    cell_icon c;
    std::unique_ptr<Item> item;
public:
    Cell();
    Cell(cell_icon ci);
    Cell(cell_icon ci, std::unique_ptr<Item> it);
};

#endif
