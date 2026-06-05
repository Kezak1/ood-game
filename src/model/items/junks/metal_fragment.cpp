#include "metal_fragment.h"
#include "junk.h"

std::string MetalFragment::type_label() const {
    return "metal_fragment";
}

MetalFragment::MetalFragment() : Junk("metal fragment") {}