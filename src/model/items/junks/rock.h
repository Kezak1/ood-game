#pragma once

#include "junk.h"

class Rock : public Junk {
public:
    std::string type_label() const override;
    Rock();
};
