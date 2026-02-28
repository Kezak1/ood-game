#ifndef CELL_H
#define CELL_H

#include "item.h"
#include "utils.h"

#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>

enum cell_icon {
    WALL,
    EMPTY,
};

class Cell {
    cell_icon c;
    std::vector<std::unique_ptr<Item>> items;
public:
    Cell();
    Cell(cell_icon ci);
    Cell(cell_icon ci, std::unique_ptr<Item> it);
    Cell(cell_icon ci, std::vector<std::unique_ptr<Item>> _items);

    cell_icon get_c() const;
    void set_c(cell_icon ci);
    
    const std::vector<std::unique_ptr<Item>>& get_items() const;
    void add_item(std::unique_ptr<Item> item);
};

#endif
