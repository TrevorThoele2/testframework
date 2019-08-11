#pragma once

#include <vector>
#include <Chroma/VariadicTemplate.h>

namespace TestFramework
{
    class DataGeneration;

    namespace detail
    {
        template<class Template>
        using ClassGroupData = typename Template::TupleT;

        template<class T>
        struct ClassDataTemplateTransformer
        {
            using Type = std::vector<T>;
        };
        template<class Template>
        using ClassGroupDataLists = typename Template::template Transform<ClassDataTemplateTransformer>::Type::TupleT;

        template<class T, class Template, ::Chroma::VariadicTemplateSize i>
        class ClassConstructor
        {
        public:
            using StackValue = T;
            using HeapValue = T*;

            using Next = ClassConstructor<T, Template, i - 1>;
            using GroupData = ClassGroupData<Template>;
            using CurrentType = typename Template::template Parameter<i - 1>::Type;

            template<class... Args>
            static StackValue CreateStack(DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static StackValue CreateStackFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static HeapValue CreateHeap(DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static HeapValue CreateHeapFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args);
        };

        template<class T, class Template>
        class ClassConstructor<T, Template, 0>
        {
        public:
            using StackValue = T;
            using HeapValue = T*;

            using GroupData = ClassGroupData<Template>;

            template<class... Args>
            static StackValue CreateStack(DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static StackValue CreateStackFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static HeapValue CreateHeap(DataGeneration& dataGeneration, Args&& ... args);
            template<class... Args>
            static HeapValue CreateHeapFrom(GroupData& data, DataGeneration& dataGeneration, Args&& ... args);
        };

        template<class Template, ::Chroma::VariadicTemplateSize i>
        class ClassGroupDataConstructor
        {
        public:
            using GroupCount = size_t;

            using Next = ClassGroupDataConstructor<Template, i - 1>;
            using GroupDataLists = ClassGroupDataLists<Template>;
            using CurrentType = typename Template::template Parameter<i - 1>::Type;

            template<class... Args>
            static GroupDataLists Create(GroupCount count, DataGeneration& dataGeneration, Args&& ... args);
        };

        template<class Template>
        class ClassGroupDataConstructor<Template, 0>
        {
        public:
            using GroupCount = size_t;

            using GroupDataLists = ClassGroupDataLists<Template>;

            template<class... Args>
            static GroupDataLists Create(GroupCount count, DataGeneration& dataGeneration, Args&& ... args);
        };

        template<class Template, ::Chroma::VariadicTemplateSize i>
        class ClassGroupDataExtractor
        {
        public:
            using GroupCount = size_t;

            using Next = ClassGroupDataExtractor<Template, i - 1>;
            using GroupData = ClassGroupData<Template>;
            using GroupDataLists = ClassGroupDataLists<Template>;

            template<class... Args>
            static GroupData Extract(GroupCount curListIndex, GroupDataLists& dataLists, Args&& ... args);
        };

        template<class Template>
        class ClassGroupDataExtractor<Template, 0>
        {
        public:
            using GroupCount = size_t;

            using GroupData = ClassGroupData<Template>;
            using GroupDataLists = ClassGroupDataLists<Template>;

            template<class... Args>
            static GroupData Extract(GroupCount curListIndex, GroupDataLists& dataLists, Args&& ... args);
        };
    }
}