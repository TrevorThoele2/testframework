#pragma once

#include <unordered_map>
#include <typeindex>
#include <any>

#include "BoolDataGenerator.h"
#include "IntegerDataGenerator.h"
#include "FloatingPointDataGenerator.h"
#include "StringDataGenerator.h"
#include "ClassDataGenerator.h"

namespace TestFramework
{
    class DataGeneration
    {
    public:
        template<class T, class... Args>
        auto Random(Args&& ... args);
        template<class T, class... Args>
        auto RandomStack();
        template<class T, class... Args>
        auto RandomHeap();
        template<class T, class... Args>
        auto RandomGroup(Args&& ... args);
        template<class T, class... Args>
        auto RandomStackGroup(GroupCount count);
        template<class T, class... Args>
        auto RandomHeapGroup(GroupCount count);
    public:
        template<class T, std::enable_if_t<!std::is_class_v<T>, int> = 0>
        DataGenerator<T>& Generator();
        template<class T, std::enable_if_t<std::is_class_v<T> && std::is_same_v<std::string, T>, int> = 0>
        DataGenerator<T>& Generator();
        template<class T, std::enable_if_t<std::is_class_v<T> && !std::is_same_v<std::string, T>, int> = 0>
        ClassDataGenerator<T>& Generator();
    private:
        using GeneratorMap = std::unordered_map<std::type_index, std::any>;
        GeneratorMap generatorMap;

        template<class T>
        DataGenerator<T>& DefinedGenerator();

        template<class T>
        std::type_index GeneratorKey();
    };

    template<class T, class... Args>
    auto DataGeneration::Random(Args&& ... args)
    {
        return Generator<T>().Random(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    auto DataGeneration::RandomStack()
    {
        return Generator<T>().template RandomStack<Args...>();
    }

    template<class T, class... Args>
    auto DataGeneration::RandomHeap()
    {
        return Generator<T>().template RandomHeap<Args...>();
    }

    template<class T, class... Args>
    auto DataGeneration::RandomGroup(Args&& ... args)
    {
        return Generator<T>().RandomGroup(std::forward<Args>(args)...);
    }

    template<class T, class... Args>
    auto DataGeneration::RandomStackGroup(GroupCount count)
    {
        return Generator<T>().template RandomStackGroup<Args...>(count);
    }

    template<class T, class... Args>
    auto DataGeneration::RandomHeapGroup(GroupCount count)
    {
        return Generator<T>().template RandomHeapGroup<Args...>(count);
    }

    template<class T, std::enable_if_t<!std::is_class_v<T>, int>>
    DataGenerator<T>& DataGeneration::Generator()
    {
        return DefinedGenerator<T>();
    }

    template<class T, std::enable_if_t<std::is_class_v<T> && std::is_same_v<std::string, T>, int>>
    DataGenerator<T>& DataGeneration::Generator()
    {
        return DefinedGenerator<T>();
    }

    template<class T, std::enable_if_t<std::is_class_v<T> && !std::is_same_v<std::string, T>, int>>
    ClassDataGenerator<T>& DataGeneration::Generator()
    {
        auto key = GeneratorKey<T>();
        auto focusedGenerator = generatorMap.find(key);
        if (focusedGenerator == generatorMap.end())
            focusedGenerator = generatorMap.emplace(key, std::any{ ClassDataGenerator<T>(*this) }).first;

        return std::any_cast<ClassDataGenerator<T>&>(focusedGenerator->second);
    }

    template<class T>
    DataGenerator<T>& DataGeneration::DefinedGenerator()
    {
        auto key = GeneratorKey<T>();
        auto focusedGenerator = generatorMap.find(key);
        if (focusedGenerator == generatorMap.end())
            focusedGenerator = generatorMap.emplace(key, std::any{ DataGenerator<T>(*this) }).first;

        return std::any_cast<DataGenerator<T>&>(focusedGenerator->second);
    }

    template<class T>
    std::type_index DataGeneration::GeneratorKey()
    {
        using StrippedT = std::remove_reference<std::remove_const_t<T>>;
        return std::type_index(typeid(StrippedT));
    }
}

#include "ClassDataGeneratorDefinitions.h"
#include "ClassDataGeneratorImplementationDefinitions.h"