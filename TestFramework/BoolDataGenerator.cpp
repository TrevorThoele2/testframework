#include "BoolDataGenerator.h"

#include <ctime>

namespace TestFramework
{
    DataGenerator<bool>::DataGenerator(DataGeneration& dataGeneration) :
        DataGeneratorBase(dataGeneration), randomEngine(static_cast<unsigned int>(time(nullptr)))
    {}

    DataGenerator<bool>::Value DataGenerator<bool>::Random()
    {
        const Distribution distribution = {};

        return static_cast<bool>(distribution(randomEngine));
    }

    DataGenerator<bool>::Group DataGenerator<bool>::RandomGroup(GroupCount count)
    {
        Group returnValue;
        if (count == 0)
            return returnValue;
        
        Distribution distribution = {};
        auto creator = [this, &distribution]()
        {
            return distribution(randomEngine);
        };

        return this->CreateExclusiveGroup<Value>(count, creator);
    }
}