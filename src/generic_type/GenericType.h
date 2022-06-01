#ifndef SEMANTIC_TYPES_TEST_PROJECT_GENERICTYPE_H
#define SEMANTIC_TYPES_TEST_PROJECT_GENERICTYPE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

namespace generic_type {

    enum class SemanticType : int{
        Translation = 0,
        Rotation
    };

    enum class DataType : int{
        SCALAR = 0,
        VECTOR2,
        VECTOR3,
        VECTOR4
    };

    enum class ScalarType : int{
        Double = 0,

    };

    template<typename T>
    struct GenericVector3 {
        using Type = T;
        using Pointer = T*;
        GenericVector3(T* ptr) : ptr_(ptr) {};

        inline T& X() {
            return ptr_[0];
        }
        inline T& Y() {
            return ptr_[1];
        }
        inline T& Z() {
            return ptr_[2];
        }

        inline T& At(int index){
            return ptr_[index];
        }

    private:
        T* ptr_;

    };

    template<typename T>
    struct GenericVector4 {
        using Type = T;
        using Pointer = T*;
        GenericVector4(Pointer ptr) : ptr_(ptr) {};

        inline T& X() {
            return ptr_[0];
        }
        inline T& Y() {
            return ptr_[1];
        }
        inline T& Z() {
            return ptr_[2];
        }
        inline T& W() {
            return ptr_[3];
        }

        inline T& At(int index){
            return ptr_[index];
        }

    private:
        Pointer ptr_;

    };



    struct GenericField {
        GenericField(int byte_offset, DataType type, ScalarType scalar_type);

        int byte_offset;
        DataType type;
        ScalarType scalar_type;
    };

    struct GenericType {
        int dimensions;
        std::vector<int> dim_size;
        std::unordered_map<SemanticType, GenericField> fields;
        uint8_t* data;

        template<SemanticType semantic_type> auto GetField();



    };



    template<>
    auto GenericType::GetField<SemanticType::Translation>() {
        auto& field = fields.at(SemanticType::Translation);
        switch (field.type) {
            case DataType::VECTOR3:
                switch (field.scalar_type) {
                    case ScalarType::Double:
                        return GenericVector3<double>(reinterpret_cast<double *>(data + field.byte_offset));
                    default:
                        assert(!"Unsupported scalar type for SemanticType::Translation");
                }
            default:
                assert(!"Unsupported field type for SemanticType::Translation");

        }
    }
    template<>
    auto GenericType::GetField<SemanticType::Rotation>() {
        auto& field = fields.at(SemanticType::Rotation);
        switch (field.type) {
            case DataType::VECTOR4:
                switch (field.scalar_type) {
                    case ScalarType::Double:
                        return GenericVector4<double>(reinterpret_cast<double *>(data + field.byte_offset));
                    default:
                        assert(!"Unsupported scalar type for SemanticType::Rotation");
                }
            default:
                assert(!"Unsupported field type for SemanticType::Rotation");
        }
    }

}




#endif //SEMANTIC_TYPES_TEST_PROJECT_GENERICTYPE_H
