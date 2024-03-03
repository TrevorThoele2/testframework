#pragma once

#include "DataGenerator.h"
#include "NumericDataGeneratorBase.h"

namespace TestFramework
{
    template<>
    class DataGenerator<float> : public NumericDataGeneratorBase<float>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<double> : public NumericDataGeneratorBase<double>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };
}