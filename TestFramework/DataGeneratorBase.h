#pragma once

namespace TestFramework
{
    class DataGeneration;

    template<class T>
    class DataGeneratorBase
    {
    public:
        typedef T Value;
        using GroupCount = size_t;
    protected:
        DataGeneration* const dataGeneration;
    protected:
        DataGeneratorBase(DataGeneration& dataGeneration);
    protected:
        template<class U, class CreationFunction>
        std::vector<U> CreateExclusiveGroup(GroupCount count, CreationFunction creator);
    };

    template<class T>
    DataGeneratorBase<T>::DataGeneratorBase(DataGeneration& dataGeneration) : dataGeneration(&dataGeneration)
    {}

    template<class T>
    template<class U, class CreationFunction>
    std::vector<U> DataGeneratorBase<T>::CreateExclusiveGroup(GroupCount count, CreationFunction creator)
    {
        std::vector<U> returnValue;
        if (count == 0)
            return returnValue;

        returnValue.reserve(count);
        for (size_t i = 0; i < count;)
        {
            auto generated = creator();

            auto found = std::find(returnValue.begin(), returnValue.end(), generated);
            if (found != returnValue.end())
                continue;
            else
            {
                returnValue.push_back(generated);
                ++i;
            }
        }

        return returnValue;
    }
}