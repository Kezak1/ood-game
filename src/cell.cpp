#include "cell.h"

Cell::Cell() : c(EMPTY), items() {}

Cell::Cell(cell_icon ci) : c(ci), items() {}

Cell::Cell(cell_icon ci, std::unique_ptr<Item> item) {
    if(ci != EMPTY) {
        throw std::invalid_argument("this constructor works only for ci == EMPTY");
    }
    c = ci;
    items.push_back(std::move(item));
}

Cell::Cell(cell_icon ci, std::vector<std::unique_ptr<Item>> _items) {
    if(ci != EMPTY) {
        throw std::invalid_argument("this constructor works only for ci == EMPTY");
    }
    c = ci;
    items = std::move(_items);
}

cell_icon Cell::get_c() const {
    return c;
} 

void Cell::set_c(cell_icon ci) {
    c = ci;
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
