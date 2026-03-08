#include "junk.h"

Junk::Junk(std::string s) : Item(s) {
}

std::string Junk::get_info() const {
    return "unusable item";
}