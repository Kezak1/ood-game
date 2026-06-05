#pragma once

#include "junk.h"

class MetalFragment : public Junk {
public:
    std::string type_label() const override;
    MetalFragment();
};
