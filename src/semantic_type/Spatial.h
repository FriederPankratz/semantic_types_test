#ifndef SEMANTIC_TYPES_TEST_PROJECT_SPATIAL_H
#define SEMANTIC_TYPES_TEST_PROJECT_SPATIAL_H

#include "SemanticType.h"

namespace semantic_type {
    template<typename Scalar>
    struct Pose6D : GenericSdType{
        Pose6D() { HeaderType = 0;};
        using Properties = make_t< Property<0,sizeof(Scalar)*0,Scalar>, Property<1,sizeof(Scalar)*1,Scalar>, Property<2,sizeof(Scalar)*2,Scalar>,
        Property<0,sizeof(Scalar)*3,Scalar>, Property<1,sizeof(Scalar)*4,Scalar>, Property<2,sizeof(Scalar)*5,Scalar>, Property<3,sizeof(Scalar)*6,Scalar>>;
        using Type = Scalar;
        static inline std::string Name{"Pose6D"};

    };

    template<typename Scalar>
    struct Translation3D : GenericSdType {
        Translation3D() {HeaderType = 1;};
        using Properties = make_t< Property<0,0,Scalar>, Property<1,1,Scalar>, Property<2,2,Scalar> >;
        using Type = Scalar;
        static inline std::string Name{"Translation3D"};
    };

    using Pose6Dd = Pose6D<double>;
    using Translation3Dd = Translation3D<double>;

    using Pose6DValue = GenericValue<Pose6Dd, void>;
}
#endif //SEMANTIC_TYPES_TEST_PROJECT_SPATIAL_H
