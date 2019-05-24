#include "StringDataGenerator.h"

#include <ctime>

namespace TestFramework
{
    DataGenerator<std::string>::DataGenerator(DataGeneration& dataGeneration) :
        DataGeneratorBase(dataGeneration), randomEngine(static_cast<unsigned int>(time(nullptr)))
    {}

    DataGenerator<std::string>::Value DataGenerator<std::string>::Random(size_t size)
    {
        if (size == 0)
            return "";

        std::string returnValue;

        std::string selectFrom = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXZ";
        std::uniform_int_distribution<unsigned int> distribution(0, selectFrom.size() - 1);

        for (unsigned int i = 0; i < size; ++i)
        {
            auto selectFromIndex = distribution(randomEngine);
            auto selected = selectFrom[selectFromIndex];
            returnValue += selected;
        }

        return returnValue;
    }

    DataGenerator<std::string>::Group DataGenerator<std::string>::RandomGroup(GroupCount count, size_t size)
    {
        if (size == 0)
            return Group();

        auto creator = [this, size]()
        {
            return Random(size);
        };
        
        return CreateExclusiveGroup<Value>(count, creator);
    }
}