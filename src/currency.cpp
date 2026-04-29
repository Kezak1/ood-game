#include "currency.h"

Currency::Currency(std::string s) : Item(s) {
}

std::string Currency::get_info() const {
    return "";
}

bool Currency::goes_to_inv() const {
    return false;
}