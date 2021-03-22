#pragma once

#include <vector>
#include <random>
#include <ctime>

#include "DataGeneratorBase.h"
#include "Range.h"
#include "RangeMinNotLessThanEqualMax.h"

namespace TestFramework
{
    namespace Detail
    {
        template<class T>
        struct DistributionResolver
        {
            using Distribution = std::uniform_int_distribution<T>;
        };

        template<>
        struct DistributionResolver<std::int8_t>
        {
            using Distribution = std::uniform_int_distribution<std::int16_t>;
        };

        template<>
        struct DistributionResolver<std::uint8_t>
        {
            using Distribution = std::uniform_int_distribution<std::uint16_t>;
        };

        template<>
        struct DistributionResolver<float>
        {
            using Distribution = std::uniform_real_distribution<float>;
        };

        template<>
        struct DistributionResolver<double>
        {
            using Distribution = std::uniform_real_distribution<double>;
        };
    }

    template<class T>
    class NumericDataGeneratorBase : public DataGeneratorBase<T>
    {
    public:
        using Value = typename DataGeneratorBase<T>::Value;
        using Group = std::vector<Value>;
    public:
        using Range = Range<Value>;
    public:
        NumericDataGeneratorBase(DataGeneration& dataGeneration);

        Value Random(Range range = Range());
        Group RandomGroup(GroupCount count, Range range = Range());
    protected:
        using DataGeneratorBase<T>::CreateExclusiveGroup;
        using DataGeneratorBase<T>::dataGeneration;
    private:
        std::default_random_engine randomEngine;

        using Distribution = typename Detail::DistributionResolver<T>::Distribution;
        Distribution ToDistribution(const Range& range);
    private:
        void ThrowIfRangeInvalid(const Range& range) const;
    private:
        static_assert(std::is_arithmetic_v<T>, "This class must manage an arithmetic type.");
    };

    template<class T>
    NumericDataGeneratorBase<T>::NumericDataGeneratorBase(DataGeneration& dataGeneration) :
        DataGeneratorBase<T>(dataGeneration), randomEngine(static_cast<unsigned int>(time(nullptr)))
    {}

    template<class T>
    typename NumericDataGeneratorBase<T>::Value NumericDataGeneratorBase<T>::Random(Range range)
    {
        ThrowIfRangeInvalid(range);

        if (range.Distance() == 0)
            return range.min;

        Distribution distribution = ToDistribution(range);

        return static_cast<T>(distribution(randomEngine));
    }

    template<class T>
    typename NumericDataGeneratorBase<T>::Group NumericDataGeneratorBase<T>::RandomGroup(GroupCount count, Range range)
    {
        ThrowIfRangeInvalid(range);

        Group returnValue;
        if (count == 0)
            return returnValue;

        auto distance = range.Distance();
        const auto percentCountTakesUpRange = static_cast<float>(static_cast<Value>(count) / distance);
        if (percentCountTakesUpRange > 0.25)
        {
            NumericDataGeneratorBase<unsigned int> indexGenerator(*dataGeneration);

            Group selectFrom;
            for (Value i = range.min; i < range.max; ++i)
                selectFrom.push_back(i);

            for (size_t i = 0; i < count; ++i)
            {
                const TestFramework::Range<unsigned int> createdRange(0, selectFrom.size() - 1);
                auto selectFromIndex = indexGenerator.Random(createdRange);
                auto selected = selectFrom[selectFromIndex];
                returnValue.push_back(selected);
            }
        }
        else
        {
            Distribution distribution = ToDistribution(range);
            auto creator = [this, &distribution]()
            {
                return distribution(randomEngine);
            };

            returnValue = this->template CreateExclusiveGroup<Value>(count, creator);
        }

        return returnValue;
    }

    template<class T>
    typename NumericDataGeneratorBase<T>::Distribution NumericDataGeneratorBase<T>::ToDistribution(const Range& range)
    {
        return Distribution(range.min, range.max);
    }

    template<class T>
    void NumericDataGeneratorBase<T>::ThrowIfRangeInvalid(const Range& range) const
    {
        if (range.min > range.max)
            throw RangeMinNotLessThanEqualMax();
    }
}