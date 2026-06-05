#include "old_book.h"

std::string OldBook::type_label() const {
    return "old_book";
}

OldBook::OldBook() : Junk("old book") {}