#pragma once

#include "units.h"

namespace MTK
{
struct Value {
    float value;
    Units unit;

    Value to(Units, float) const;
    void norm();
};

} // namespace MTK
