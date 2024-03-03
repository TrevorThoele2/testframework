#pragma once

#include "DataGeneratorBase.h"
#include "ClassDataGeneratorImplementation.h"

namespace TestFramework
{
    template<class T>
    class ClassDataGenerator : public DataGeneratorBase<T>
    {
    public:
        using StackValue = typename DataGeneratorBase<T>::Value;
        using StackGroup = std::vector<StackValue>;
        using HeapValue = StackValue*;
        using HeapGroup = std::vector<HeapValue>;
    public:
        ClassDataGenerator(DataGeneration& dataGeneration);

        template<class... Args>
        StackValue RandomStack();
        template<class... Args>
        HeapValue RandomHeap();

        template<class... Args>
        StackGroup RandomStackGroup(GroupCount count);
        template<class... Args>
        HeapGroup RandomHeapGroup(GroupCount count);
    protected:
        using DataGeneratorBase<T>::dataGeneration;
    private:
        template<class Template>
        using GroupData = detail::ClassGroupData<Template>;
        template<class Template>
        using GroupDataLists = detail::ClassGroupDataLists<Template>;

        template<class Template, ::Chroma::VariadicTemplateSize i>
        using Constructor = detail::ClassConstructor<T, Template, i>;
        template<class Template, ::Chroma::VariadicTemplateSize i>
        using GroupDataConstructor = detail::ClassGroupDataConstructor<Template, i>;
        template<class Template, ::Chroma::VariadicTemplateSize i>
        using GroupDataExtractor = detail::ClassGroupDataExtractor<Template, i>;
    };
}