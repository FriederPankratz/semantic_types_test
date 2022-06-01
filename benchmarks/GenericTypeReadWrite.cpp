#include <benchmark/benchmark.h>
#include <iostream>

#include <generic_type/GenericType.h>
#include <TestUtils.h>

class BasicPoseVectorFixture : public benchmark::Fixture {
public:


    void SetUp(const ::benchmark::State& state) {
        using namespace generic_type;

        generic_value.data = reinterpret_cast<uint8_t *>(data_buffer.data());
        generic_value.dimensions = 0;
        generic_value.fields.emplace(SemanticType::Translation, GenericField(0, DataType::VECTOR3, ScalarType::Double));
        generic_value.fields.emplace(SemanticType::Rotation, GenericField(sizeof(double) * 3, DataType::VECTOR4, ScalarType::Double));

    }

    void TearDown(const ::benchmark::State& state) {
    }
    std::vector<double> data_buffer{test_utils::exp_px, test_utils::exp_py, test_utils::exp_pz, test_utils::exp_rx, test_utils::exp_ry, test_utils::exp_rz, test_utils::exp_rw};
    generic_type::GenericType generic_value;
};

BENCHMARK_DEFINE_F(BasicPoseVectorFixture, ReadVector)(benchmark::State& state){

    using namespace test_utils;
    using namespace generic_type;

    for (auto _ : state){
        double px = data_buffer[0];
        double py = data_buffer[1];
        double pz = data_buffer[2];

        benchmark::DoNotOptimize(px);
        benchmark::DoNotOptimize(py);
        benchmark::DoNotOptimize(pz);
        benchmark::DoNotOptimize(data_buffer.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(BasicPoseVectorFixture, WriteVector)(benchmark::State& state){

    using namespace test_utils;
    using namespace generic_type;

    for (auto _ : state){
        data_buffer[0] = exp_px;
        data_buffer[1] = exp_py;
        data_buffer[2] = exp_pz;

        benchmark::DoNotOptimize(data_buffer.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(BasicPoseVectorFixture, ReadGenericType) (benchmark::State& state){

    using namespace test_utils;
    using namespace generic_type;

    for (auto _ : state){
        auto position = generic_value.GetField<SemanticType::Translation>();
        double px = position.X();
        double py = position.Y();
        double pz = position.Z();

        benchmark::DoNotOptimize(px);
        benchmark::DoNotOptimize(py);
        benchmark::DoNotOptimize(pz);
        benchmark::DoNotOptimize(data_buffer.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(BasicPoseVectorFixture, WriteGenericType) (benchmark::State& state){

    using namespace test_utils;
    using namespace generic_type;

    for (auto _ : state){
        auto position = generic_value.GetField<SemanticType::Translation>();
        position.X() = exp_px;
        position.Y() = exp_py;
        position.Z() = exp_pz;

        benchmark::DoNotOptimize(data_buffer.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK_DEFINE_F(BasicPoseVectorFixture, WriteGenericTypeWithoutFieldConstruciton) (benchmark::State& state){

    using namespace test_utils;
    using namespace generic_type;

    auto position = generic_value.GetField<SemanticType::Translation>();
    for (auto _ : state){

        position.X() = exp_px;
        position.Y() = exp_py;
        position.Z() = exp_pz;

        benchmark::DoNotOptimize(data_buffer.data());
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(BasicPoseVectorFixture, ReadVector);
BENCHMARK_REGISTER_F(BasicPoseVectorFixture, ReadGenericType);
BENCHMARK_REGISTER_F(BasicPoseVectorFixture, WriteVector);
BENCHMARK_REGISTER_F(BasicPoseVectorFixture, WriteGenericType);
BENCHMARK_REGISTER_F(BasicPoseVectorFixture, WriteGenericTypeWithoutFieldConstruciton);
