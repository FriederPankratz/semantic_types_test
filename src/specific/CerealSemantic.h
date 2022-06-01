#ifndef SEMANTIC_TYPES_TEST_PROJECT_CEREALSEMANTIC_H
#define SEMANTIC_TYPES_TEST_PROJECT_CEREALSEMANTIC_H

#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <type_traits>
#include <fmt/format.h>

#include <semantic_type/Spatial.h>


namespace cereal {

    template<class Archive, typename PROP>  inline
    void WriteSingleSDTProperty(const void* value, Archive& ar)  {
        using ResultType = typename PROP::Type;
        const uint8_t * pValue = static_cast<const uint8_t *>(value) + PROP::Offset;
        const auto* p2 = reinterpret_cast<const ResultType *>(pValue);
        //const auto* pValue = static_cast<const ResultType*>(value);

        ar(cereal::make_nvp(semantic_type::traits::property_to_values<PROP>::name, *p2));


    }

    template<class Archive, typename PROP> inline
    void WriteSDTProperty(const void* value, Archive& ar) {

        WriteSingleSDTProperty<Archive, typename PROP::head>(value, ar);
        if constexpr(!std::is_same_v<typename PROP::tail, semantic_type::mynull_t>){
            WriteSDTProperty<Archive, typename PROP::tail>(value, ar);
        }
    }

    template<class Archive, typename PROP_GROUP> inline
    void WriteSDTSinglePropertyGroup(const void* value, Archive& ar) {

        //ar(cereal::make_nvp(semantic_type::traits::property_group_to_values<PROP_GROUP>::name, ));

        std::cout << semantic_type::traits::property_group_to_values<PROP_GROUP>::name << "\n";
        WriteSDTProperty<Archive, typename PROP_GROUP::Properties>(value, ar);

    }

    template<class Archive, typename PROP_GROUP > inline
    void WriteSDTPropertyGroup(const void* value, Archive& ar) {

        WriteSDTSinglePropertyGroup<Archive, typename PROP_GROUP::head>(value, ar);
        if constexpr(!std::is_same_v<typename PROP_GROUP::tail, semantic_type::mynull_t>){
            WriteSDTPropertyGroup<Archive, typename PROP_GROUP::tail>(value, ar);
        }
    }
//
//    template<typename Header>
//    std::ostream& WriteSDTData(const Header* header,const void* value, std::ostream& stream) {
//
//        stream << Header::Name << "\n";
//        WriteSDTProperty<typename Header::Properties>(value, stream);
//
//        return stream;
//    }


    template<class Archive, typename Header, typename Data>
    [[maybe_unused]] void WriteProperties(const Header* header,const Data* value, Archive& ar) {
        WriteSDTProperty<Archive, typename Header::Properties>(value, ar);

    }

//    using SDTHeader = semantic_type::GenericSdType*;
//    using SDTData = void*;
//    template<class Archive>
//    void WriteProperties<Archive, SDTHeader , SDTData>(const SDTHeader& header,const SDTData & value, Archive& ar) {
//
//
//    }

    template<class Archive>
    inline void save(Archive &ar, const semantic_type::DefaultValue &value) {


        switch (value.header->HeaderType) {
            case 0: {
                WriteProperties(static_cast<const semantic_type::Pose6Dd*>(value.header), value.data, ar);
                return;
            }



            case 1: {
                return;
            }

            default:{
                ar(cereal::make_nvp("foobar error", 5));
            }

        }
    };

    template<class Archive, typename Data, typename... Ts>
    void WriteDynamicProp2(Archive& ar,const Data* value, std::tuple<Ts...> const& theTuple)
    {
        //std::cout << "sdfsdf\n";
        auto foo = [&ar](Ts const&... tupleArgs)
        {
            ar((cereal::make_nvp(std::to_string(tupleArgs.Name), tupleArgs.Offset), ...));
            //ar(cereal::make_nvp("foobar error", ((cereal::make_nvp("sdf", tupleArgs.Offset)), ...)));

        };
        std::apply(foo, theTuple);

    }

    template<class Archive, typename Header, typename Data>
    [[maybe_unused]] void WriteDynamicProperties(const Header* header,const Data* value, Archive& ar) {

        WriteDynamicProp2(ar, value, header->values);


    }

    template<class Archive>
    inline void save(Archive &ar, const dynamic_type::DefaultValue &value) {


        switch (value.header->HeaderType) {
            case 0: {
                WriteDynamicProperties(static_cast<const dynamic_type::Pose6Dd*>(value.header), value.data, ar);
                return;
            }



            case 1: {
                return;
            }

            default:{
                ar(cereal::make_nvp("foobar error", 5));
            }

        }
    };
}

#endif //SEMANTIC_TYPES_TEST_PROJECT_CEREALSEMANTIC_H
