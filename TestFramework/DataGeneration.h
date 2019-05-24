#pragma once

#include <unordered_map>
#include <typeindex>

#include "IntegerDataGenerator.h"
#include "FloatingPointDataGenerator.h"
#include "StringDataGenerator.h"
#include "ClassDataGenerator.h"

#include <Chroma/Any.h>

namespace TestFramework
{
    class DataGeneration
    {
    public:
        template<class T, std::enable_if_t<!std::is_class_v<T>, int> = 0>
        DataGenerator<T>& Generator();
        template<class T, std::enable_if_t<std::is_class_v<T> && std::is_same_v<std::string, T>, int> = 0>
        DataGenerator<T>& Generator();
        template<class T, std::enable_if_t<std::is_class_v<T> && !std::is_same_v<std::string, T>, int> = 0>
        ClassDataGenerator<T>& Generator();
    private:
        using GeneratorMap = std::unordered_map<std::type_index, ::Chroma::Any>;
        GeneratorMap generatorMap;

        template<class T>
        DataGenerator<T>& DefinedGenerator();

        template<class T>
        std::type_index GeneratorKey();
    };

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
            focusedGenerator = generatorMap.emplace(key, ::Chroma::Any(ClassDataGenerator<T>(*this))).first;

        return focusedGenerator->second.As<ClassDataGenerator<T>>();
    }

    template<class T>
    DataGenerator<T>& DataGeneration::DefinedGenerator()
    {
        auto key = GeneratorKey<T>();
        auto focusedGenerator = generatorMap.find(key);
        if (focusedGenerator == generatorMap.end())
            focusedGenerator = generatorMap.emplace(key, ::Chroma::Any(DataGenerator<T>(*this))).first;

        return focusedGenerator->second.As<DataGenerator<T>>();
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