#ifndef CELL_H
#define CELL_H

#include "item.h"
#include "utils.h"

#include <memory>
#include <vector>
#include <stdexcept>
#include <utility>

class Cell {
    bool wall;
    std::vector<std::unique_ptr<Item>> items;
public:
    Cell();
    Cell(bool is_wall);
    Cell(bool is_wall, std::unique_ptr<Item> item);
    Cell(bool is_wall, std::vector<std::unique_ptr<Item>> _items);

    bool is_wall() const;
    void set_wall(bool is_wall);
    
    const std::vector<std::unique_ptr<Item>>& get_items() const;

    bool no_items() const; 
    
    void add_item(std::unique_ptr<Item> item);
    std::unique_ptr<Item> take_item(int idx);
};

#endif
