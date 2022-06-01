#include <benchmark/benchmark.h>
#include <iostream>

#include <cereal/archives/json.hpp>
#include <specific/CerealEigen.h>
#include <TestUtils.h>

static void CerealEigenAsJson (benchmark::State& state){
    using namespace test_utils;

    Eigen::Affine3d pose = Eigen::Translation3d(exp_px,exp_py,exp_pz) * Eigen::Quaterniond(exp_rw,exp_rx,exp_ry,exp_rz);

        for (auto _ : state){
            std::stringstream ss;
            {
                cereal::JSONOutputArchive archive_(ss);
                archive_(pose);
            }
            auto json_pose = ss.str();
            benchmark::DoNotOptimize(json_pose.data());
            benchmark::ClobberMemory();
        }





}

BENCHMARK(CerealEigenAsJson);
