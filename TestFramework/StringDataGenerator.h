#pragma once

#include <random>
#include <string>

#include "DataGenerator.h"
#include "DataGeneratorBase.h"

namespace TestFramework
{
    template<>
    class DataGenerator<std::string> : public DataGeneratorBase<std::string>
    {
    public:
        using Group = std::vector<Value>;
    public:
        DataGenerator(DataGeneration& dataGeneration);

        Value Random(size_t size = 10);
        Group RandomGroup(GroupCount count, size_t size = 10);
    private:
        std::default_random_engine randomEngine;
    };
}