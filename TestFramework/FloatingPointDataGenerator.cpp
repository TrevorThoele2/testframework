#include "FloatingPointDataGenerator.h"

namespace TestFramework
{
    DataGenerator<float>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<double>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}
}