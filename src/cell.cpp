#include "cell.h"

#include <stdexcept>
#include <utility>

Cell::Cell() : c(EMPTY), item(nullptr) {}

Cell::Cell(cell_icon ci) : c(ci), item(nullptr) {}

Cell::Cell(cell_icon ci, std::unique_ptr<Item> it) {
    if(ci != EMPTY) {
        throw std::invalid_argument("this constructor works only for ci == EMPTY");
    }
    c = ci;
    item = std::move(it);
}