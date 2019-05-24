#pragma once

#include "NumericDataGeneratorBase.h"

namespace TestFramework
{
    template<>
    class DataGenerator<std::int8_t> : public NumericDataGeneratorBase<std::int8_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::int16_t> : public NumericDataGeneratorBase<std::int16_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::int32_t> : public NumericDataGeneratorBase<std::int32_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::int64_t> : public NumericDataGeneratorBase<std::int64_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::uint8_t> : public NumericDataGeneratorBase<std::uint8_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::uint16_t> : public NumericDataGeneratorBase<std::uint16_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::uint32_t> : public NumericDataGeneratorBase<std::uint32_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };

    template<>
    class DataGenerator<std::uint64_t> : public NumericDataGeneratorBase<std::uint64_t>
    {
    public:
        DataGenerator(DataGeneration& dataGeneration);
    };
}