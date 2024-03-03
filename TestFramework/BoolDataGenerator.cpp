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
        
        const Distribution distribution = {};

        Group group;
        for (GroupCount i = 0; i < count; ++i)
            group.push_back(distribution(randomEngine));
        return group;
    }
}