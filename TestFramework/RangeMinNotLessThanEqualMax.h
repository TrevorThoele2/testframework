#pragma once

#include <stdexcept>

namespace TestFramework
{
    class RangeMinNotLessThanEqualMax : public ::std::runtime_error
    {
    public:
        RangeMinNotLessThanEqualMax();
    };
}