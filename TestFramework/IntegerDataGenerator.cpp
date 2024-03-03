#include "IntegerDataGenerator.h"

namespace TestFramework
{
    DataGenerator<std::int8_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::int16_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::int32_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::int64_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::uint8_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::uint16_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::uint32_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}

    DataGenerator<std::uint64_t>::DataGenerator(DataGeneration& dataGeneration) : NumericDataGeneratorBase(dataGeneration)
    {}
}