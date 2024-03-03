#pragma once

#include <vector>
#include <random>

#include "DataGenerator.h"
#include "DataGeneratorBase.h"

namespace TestFramework
{
    template<>
    class DataGenerator<bool> : public DataGeneratorBase<bool>
    {
    public:
        using Group = std::vector<Value>;
    public:
        DataGenerator(DataGeneration& dataGeneration);

        Value Random();
        Group RandomGroup(GroupCount count);
    private:
        std::default_random_engine randomEngine;

        using Distribution = std::bernoulli_distribution;
    };
}