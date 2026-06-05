#pragma once

#include "junk.h"

class OldBook : public Junk {
public:
    std::string type_label() const override;
    OldBook();
};
