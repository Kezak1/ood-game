#include "rock.h"

std::string Rock::type_label() const {
    return "rock";
}

Rock::Rock() : Junk("rock") {}