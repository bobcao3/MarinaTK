#include "value.h"

#include "glm/glm.hpp"

namespace MTK
{

Value Value::to(Units t, float v = 0.0) const
{
    switch (unit) {
    case Pixel:
        switch (t) {
        case None:
            return { value, None };
        case Pixel:
            return { value, Pixel };
        case Dot:
            return { value / v * standard_DPI, Dot }; // v = DPI
        case Percent:
            return { value / v, Percent }; // v = Max
        }
    case Dot:
        switch (t) {
        case None:
            return { value, None };
        case Pixel:
            return { value * v, Pixel }; // v = DPI
        case Dot:
            return { value, Dot };
        case Percent:
            return { value / v, Percent }; // v = Max
        }
    case Percent:
        if (t != None) {
            return { value * v, t };
        } else {
            return { value, None };
        }
    default:
        return { value, t };
    }
}

void Value::norm() {
    switch (unit) {
    case Percent:
        value = glm::clamp(value, 0.0f, 1.0f);
    default:
        return;
    }
}

} // namespace MTK
