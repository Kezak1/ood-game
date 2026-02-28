#include "cell.h"


Cell::Cell() : c(' '), item(nullptr) {}

Cell::Cell(Cells cc) {
    if(cc == WALL) {
        c = ' ';
    }
}