#ifndef DATATYPE_BENCHMARKS_PROJECT_SDTYPES_H
#define DATATYPE_BENCHMARKS_PROJECT_SDTYPES_H

#include <array>
#include <tuple>
#include <stdexcept>

namespace semantic_type {
    struct mynull_t {};

    template <typename T, typename U>
    struct tl
    {
        using head = T;
        using tail = U;
    };
    template <typename ... Ts> struct make;

// Case: Normal recursion. Consume one type per call.
    template <typename T, typename ... REST>
    struct make<T, REST...> {
        using type = tl<T, typename make<REST...>::type>;
    };

// Case: Recursion abort, because the list of types ran empty
    template <>
    struct make<> { using type = mynull_t; };

    template <typename ... Ts>
    using make_t = typename make<Ts...>::type;
    template <typename TList>
    struct list_content;

    template <typename Head, typename Tail>
    struct list_content<tl<Head, Tail>> {
    using head = Head;
    using tail = Tail;
};

template <>
struct list_content<mynull_t> {
    using head = mynull_t;
    using tail = mynull_t;
};

template <typename TList>
using head_t = typename list_content<TList>::head;

template <typename TList>
using tail_t = typename list_content<TList>::tail;
    // Function declaration: Takes a list, and a type.
// Using (list, type) notation in following comments
    template <typename TList, typename T>
    struct append;

// (empty list, null_t item) -> Still an empty list
    template <>
    struct append<mynull_t, mynull_t> { using type = mynull_t; };

// (empty list, T) -> List which only contains T
// This is usually the recursion abort step when adding an item to a list
    template <typename T>
    struct append<mynull_t, T> { using type = tl<T, mynull_t>; };

// (list, T) -> Recurse until tail of list, and return a version with T at its end
    template <typename Head, typename Tail, typename T>
    struct append<tl<Head, Tail>, T>
{ using type = tl<Head, typename append<Tail, T>::type>; };

template <typename TList, typename T>
using append_t = typename append<TList, T>::type;


//**-------------------------------------------------------------------------------------

    template<int name, int offset, typename T> struct Property {
        static constexpr int Name = name;
        static constexpr int Offset = offset;
        using Type = T;
    };

    template<int name, typename ...T> struct PropertyGroup {
        static constexpr int Name = name;
        using Properties = make_t<T...>;
    };


    struct GenericSdType {
        int HeaderType{-1};

    };

    template <typename ... Types> struct PropertyList {};





    namespace traits {
        template <typename PROP>
        struct property_to_values;

        template <int Offset, typename Scalar>
        struct property_to_values<Property<0, Offset, Scalar> > {
            static inline std::string name{"x"};
        };
        template <int Offset, typename Scalar>
        struct property_to_values<Property<1, Offset,Scalar>> {
            static inline std::string name{"y"};
        };
        template <int Offset, typename Scalar>
        struct property_to_values<Property<2, Offset,Scalar>> {
            static inline std::string name{"z"};
        };

        template <int Offset, typename Scalar>
        struct property_to_values<Property<3, Offset, Scalar> > {
            static inline std::string name{"w"};
        };



        template <typename PROP>
        struct property_group_to_values;

        template <typename PROP_LIST>
        struct property_group_to_values<PropertyGroup<0, PROP_LIST> > {
            static inline std::string name{"translation"};
        };
        template <typename PROP_LIST>
        struct property_group_to_values<PropertyGroup<1, PROP_LIST> > {
            static inline std::string name{"rotation"};
        };
    }




    template<typename HeaderType, typename ValueType>
    struct GenericValue {
        GenericValue(HeaderType *header, void *data) : header(header), data(data) {}

        HeaderType* header;
        ValueType* data;
    };

    using DefaultValue = GenericValue<GenericSdType, void>;


}

namespace dynamic_type {

    enum class ContentTypes : uint8_t {
        NONE = 0x00,
        GENERIC = 0x01,
        IMAGE = 0x02,
        GEOMETRY = 0x03,
        TRANSFORM = 0x04,
        MATCH = 0xFF
    };

    enum class TransformFormatTypes : uint8_t {
        NONE = 0x00,
        TRANSLATION = 0x01,
        ROTATION = 0x02,
        SCALING = 0x03,
        RIGID_TRANSFORM = 0x04,
        SIMILARITY_TRANSFORM = 0x05,
        AFFINE_TRANSFORM = 0x06,
        PROJECTIVE_TRANSFORM = 0x07,
        MATCH = 0xFF
    };

    enum DataStruct : uint8_t {
        INVALID = 0,
        SCALAR = 1,
        VECTOR2 = 2,
        VECTOR3 = 3,
        VECTOR4 = 4,

    } ;

    // TODO extend transformFormatTypes and structType to semantic types
    template<int name, TransformFormatTypes transformFormatTypes, DataStruct structType, typename T> struct Property {
        const int Name{name};
        const  TransformFormatTypes SemanticType{transformFormatTypes};
        const  DataStruct StructType{structType};
        using Type = T;
        int Offset;

        Property(int offset) : Offset(offset) {}
    };

    template<int name, typename T> struct PropertyGroup {
        static constexpr int Name = name;
        using Properties = T;
        Properties values;

        PropertyGroup(Properties values) : values(values) {}
    };


    struct GenericType {
        GenericType(int type) : HeaderType{type} {};

        int HeaderType;
    };

    template<typename HeaderType, typename ValueType>
    struct GenericValue {
        GenericValue(HeaderType *header, void *data) : header(header), data(data) {}

        HeaderType* header;
        ValueType* data;
    };

    using DefaultValue = GenericValue<GenericType, void>;


    template<typename Scalar>
    using TranslationProperty = Property<0,TransformFormatTypes::TRANSLATION, DataStruct::VECTOR3,Scalar>;

    template<typename Scalar>
    using RotationProperty = Property<1,TransformFormatTypes::ROTATION, DataStruct::VECTOR4,Scalar>;

    template<typename Scalar>
    struct Pose6D : GenericType {
        using Properties = std::tuple<TranslationProperty<Scalar>, RotationProperty<Scalar>>;
        const Properties values;

        Pose6D() : GenericType(0), values{TranslationProperty<Scalar>(0), RotationProperty<Scalar>(sizeof(Scalar)*3) }{

        }
    };

    using Pose6Dd = Pose6D<double>;


}

#endif //DATATYPE_BENCHMARKS_PROJECT_SDTYPES_H
