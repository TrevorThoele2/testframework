#pragma once

#include <limits>

namespace TestFramework
{
    template<class T>
    struct Range
    {
        using Value = T;

        Value min;
        Value max;

        Range();
        Range(Value min, Value max);

        Value Distance() const;
    };

    template<class T>
    Range<T>::Range() : min(std::numeric_limits<T>::min()), max(std::numeric_limits<T>::max())
    {}

    template<class T>
    Range<T>::Range(Value min, Value max) : min(min), max(max)
    {}

    template<class T>
    typename Range<T>::Value Range<T>::Distance() const
    {
        return max - min;
    }
}