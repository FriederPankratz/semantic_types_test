#include <benchmark/benchmark.h>
#include <iostream>

#include <cereal/archives/json.hpp>
#include <specific/CerealSemantic.h>
#include <TestUtils.h>
static void CerealSemanticAsJson (benchmark::State& state){

    using namespace test_utils;
    using namespace semantic_type;


    std::vector<double> data_buffer{exp_px, exp_py, exp_pz, exp_rx, exp_ry, exp_rz, exp_rw};
    Pose6Dd data_header;

    for (auto _ : state){
        std::stringstream ss;
        {
            cereal::JSONOutputArchive archive_(ss);
            archive_(DefaultValue {&data_header, std::data(data_buffer) });
        }
        auto json_pose = ss.str();
        benchmark::DoNotOptimize(json_pose.data());
        benchmark::ClobberMemory();
    }





}

BENCHMARK(CerealSemanticAsJson);