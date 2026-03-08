#include "cell.h"

Cell::Cell() : wall(false), items() {}

Cell::Cell(bool is_wall) : wall(is_wall), items() {}

Cell::Cell(bool is_wall, std::unique_ptr<Item> item) {
    if(is_wall) {
        throw std::invalid_argument("wall cells cannot store items");
    }
    wall = is_wall;
    items.push_back(std::move(item));
}

Cell::Cell(bool is_wall, std::vector<std::unique_ptr<Item>> _items) {
    if(is_wall) {
        throw std::invalid_argument("wall cells cannot store items");
    }
    wall = is_wall;
    items = std::move(_items);
}

bool Cell::is_wall() const {
    return wall;
}

void Cell::set_wall(bool is_wall) {
    wall = is_wall;
}


const std::vector<std::unique_ptr<Item>>& Cell::get_items() const {
    return items;
}

/*
const std::unique_ptr<Item>& Cell::get_item(int idx) const {
    if(idx < 1 || idx > (int)items.size()) {
        throw std::out_of_range("idx");
    }
    return items[idx - 1];
}
*/

bool Cell::empty() const {
    return items.empty();
}

void Cell::add_item(std::unique_ptr<Item> item) {
    items.push_back(std::move(item));
}

std::unique_ptr<Item> Cell::take_item(int idx) {
    if(idx < 1 || idx > (int)items.size()) {
        throw std::out_of_range("idx");
    }
    auto res = std::move(items[idx - 1]);
    items.erase(items.begin() + idx - 1);
    return res;
}
