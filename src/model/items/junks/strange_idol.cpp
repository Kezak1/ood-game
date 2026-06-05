#include "strange_idol.h"

StrangeIdol::StrangeIdol() : Junk("strange idol") {
}

std::string StrangeIdol::type_label() const {
    return "strange_idol";
}