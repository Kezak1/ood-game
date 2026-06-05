#pragma once

#include "junk.h"

class StrangeIdol : public Junk {
public:
    std::string type_label() const override;
    StrangeIdol();
};
