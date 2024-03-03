#pragma once

#include "ClassDataGenerator.h"
#include <Chroma/IsBracesConstructible.h>

namespace TestFramework
{
    template<class T>
    ClassDataGenerator<T>::ClassDataGenerator(DataGeneration& dataGeneration) : DataGeneratorBase<T>(dataGeneration)
    {}

    template<class T>
    template<class... Args>
    typename ClassDataGenerator<T>::StackValue ClassDataGenerator<T>::RandomStack()
    {
        static_assert(Chroma::is_braces_constructible_v<T, Args...>, "T is not constructible from Args.");

        using Template = Chroma::VariadicTemplate<Args...>;
        return Constructor<Template, Template::count>::CreateStack(*dataGeneration);
    }

    template<class T>
    template<class... Args>
    typename ClassDataGenerator<T>::HeapValue ClassDataGenerator<T>::RandomHeap()
    {
        static_assert(Chroma::is_braces_constructible_v<T, Args...>, "T is not constructible from Args.");

        using Template = Chroma::VariadicTemplate<Args...>;
        return Constructor<Template, Template::count>::CreateHeap(*dataGeneration);
    }

    template<class T>
    template<class... Args>
    typename ClassDataGenerator<T>::StackGroup ClassDataGenerator<T>::RandomStackGroup(GroupCount count)
    {
        static_assert(Chroma::is_braces_constructible_v<T, Args...>, "T is not constructible from Args.");

        using Template = Chroma::VariadicTemplate<Args...>;
        using Data = GroupData<Template>;

        auto dataLists = GroupDataConstructor<Template, Template::count>::Create(count, *dataGeneration);

        StackGroup returnValue;
        for (GroupCount i = 0; i < count; ++i)
        {
            Data data = GroupDataExtractor<Template, Template::count>::Extract(i, dataLists);
            returnValue.push_back(Constructor<Template, Template::count>::CreateStackFrom(data, *dataGeneration));
        }

        return returnValue;
    }

    template<class T>
    template<class... Args>
    typename ClassDataGenerator<T>::HeapGroup ClassDataGenerator<T>::RandomHeapGroup(GroupCount count)
    {
        static_assert(Chroma::is_braces_constructible_v<T, Args...>, "T is not constructible from Args.");

        using Template = Chroma::VariadicTemplate<Args...>;
        using Data = GroupData<Template>;

        auto dataLists = GroupDataConstructor<Template, Template::count>::Create(count, *dataGeneration);

        HeapGroup returnValue;
        for (GroupCount i = 0; i < count; ++i)
        {
            Data data = GroupDataExtractor<Template, Template::count>::Extract(i, dataLists);
            returnValue.push_back(Constructor<Template, Template::count>::CreateHeapFrom(data, *dataGeneration));
        }

        return returnValue;
    }
}