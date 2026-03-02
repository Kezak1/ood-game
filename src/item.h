#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    std::string name;
    // virtual ~Item() = default;
    Item() : name("item") {}
    Item(std::string s) : name(s) {}
};

#endif