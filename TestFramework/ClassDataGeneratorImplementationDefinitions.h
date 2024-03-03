#pragma once

#include "ClassDataGeneratorImplementation.h"

namespace TestFramework
{
    namespace detail
    {
        template<class T, class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassConstructor<T, Template, i>::StackValue
            ClassConstructor<T, Template, i>::CreateStack(DataGeneration& dataGeneration, Args&& ... args)
        {
            auto& generator = dataGeneration.Generator<CurrentType>();
            auto generated = generator.Random();
            return Next::CreateStack(dataGeneration, generated, std::forward<Args>(args)...);
        }

        template<class T, class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassConstructor<T, Template, i>::StackValue
            ClassConstructor<T, Template, i>::CreateStackFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args)
        {
            return Next::CreateStackFrom(data, dataGeneration, std::get<i - 1>(data), std::forward<Args>(args)...);
        }

        template<class T, class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassConstructor<T, Template, i>::HeapValue
            ClassConstructor<T, Template, i>::CreateHeap(DataGeneration& dataGeneration, Args&& ... args)
        {
            auto& generator = dataGeneration.Generator<CurrentType>();
            auto generated = generator.Random();
            return Next::CreateHeap(dataGeneration, generated, std::forward<Args>(args)...);
        }

        template<class T, class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassConstructor<T, Template, i>::HeapValue
            ClassConstructor<T, Template, i>::CreateHeapFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args)
        {
            return Next::CreateHeapFrom(data, dataGeneration, std::get<i - 1>(data), std::forward<Args>(args)...);
        }

        template<class T, class Template>
        template<class... Args>
        typename ClassConstructor<T, Template, 0>::StackValue
            ClassConstructor<T, Template, 0>::CreateStack(DataGeneration& dataGeneration, Args&& ... args)
        {
            return T(std::forward<Args>(args)...);
        }

        template<class T, class Template>
        template<class... Args>
        typename ClassConstructor<T, Template, 0>::StackValue
            ClassConstructor<T, Template, 0>::CreateStackFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args)
        {
            return T(std::forward<Args>(args)...);
        }

        template<class T, class Template>
        template<class... Args>
        typename ClassConstructor<T, Template, 0>::HeapValue
            ClassConstructor<T, Template, 0>::CreateHeap(DataGeneration& dataGeneration, Args&& ... args)
        {
            return new T(std::forward<Args>(args)...);
        }

        template<class T, class Template>
        template<class... Args>
        typename ClassConstructor<T, Template, 0>::HeapValue
            ClassConstructor<T, Template, 0>::CreateHeapFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args)
        {
            return new T(std::forward<Args>(args)...);
        }

        template<class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassGroupDataConstructor<Template, i>::GroupDataLists
            ClassGroupDataConstructor<Template, i>::Create(GroupCount count, DataGeneration& dataGeneration, Args&& ... args)
        {
            auto& generator = dataGeneration.Generator<CurrentType>();
            auto generated = generator.RandomGroup(count);
            return Next::Create(count, dataGeneration, generated, std::forward<Args>(args)...);
        }

        template<class Template>
        template<class... Args>
        typename ClassGroupDataConstructor<Template, 0>::GroupDataLists
            ClassGroupDataConstructor<Template, 0>::Create(GroupCount count, DataGeneration& dataGeneration, Args&& ... args)
        {
            return GroupDataLists(std::forward<Args>(args)...);
        }

        template<class Template, ::Chroma::VariadicTemplateSize i>
        template<class... Args>
        typename ClassGroupDataExtractor<Template, i>::GroupData
            ClassGroupDataExtractor<Template, i>::Extract(GroupCount curListIndex, GroupDataLists& dataLists, Args&& ... args)
        {
            return Next::Extract(curListIndex, dataLists, std::get<i - 1>(dataLists)[curListIndex], std::forward<Args>(args)...);
        }

        template<class Template>
        template<class... Args>
        typename ClassGroupDataExtractor<Template, 0>::GroupData
            ClassGroupDataExtractor<Template, 0>::Extract(GroupCount curListIndex, GroupDataLists& dataLists, Args&& ... args)
        {
            return GroupData(std::forward<Args>(args)...);
        }
    }
}