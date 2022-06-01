add_library(semantic_types SHARED
        semantic_cereal/CerealWriteable.cpp
        semantic_cereal/CerealWriteable.h
        semantic_cereal/CerealWriter.cpp
        semantic_cereal/CerealWriter.h
        semantic_type/SemanticType.h
        semantic_type/SemanticType.cpp specific/CerealEigen.h semantic_type/Spatial.h TestUtils.h specific/CerealSemantic.h generic_type/GenericType.cpp generic_type/GenericType.h)

target_include_directories(semantic_types PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

conan_target_link_libraries(semantic_types)