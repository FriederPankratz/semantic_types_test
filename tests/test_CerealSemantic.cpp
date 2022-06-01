#include <gtest/gtest.h>

#include <iostream>
#include <cereal/archives/json.hpp>
#include <nlohmann/json.hpp>



#include <semantic_type/Spatial.h>
#include "gtest_utils.h"
#include <specific/CerealSemantic.h>

TEST(CerealSemantic, Save) {

    std::stringstream ss;
    using namespace test_utils;
    using namespace semantic_type;


    std::vector<double> data_buffer{exp_px, exp_py, exp_pz, exp_rx, exp_ry, exp_rz, exp_rw};
    Pose6Dd data_header;

    {
        cereal::JSONOutputArchive archive_(ss);

        archive_(DefaultValue {&data_header, std::data(data_buffer) });
    }
    std::cout << ss.str() << "\n";

    auto json = nlohmann::json::parse(ss.str());

    TestCerealSave(ss.str());
}

TEST(CerealDynamicSemantic, Save) {

    std::stringstream ss;
    using namespace test_utils;
    using namespace dynamic_type;


    std::vector<double> data_buffer{exp_px, exp_py, exp_pz, exp_rx, exp_ry, exp_rz, exp_rw};
    Pose6Dd data_header;

    {
        cereal::JSONOutputArchive archive_(ss);

        archive_(DefaultValue {&data_header, std::data(data_buffer) });
    }
    std::cout << ss.str() << "\n";

    auto json = nlohmann::json::parse(ss.str());

    TestCerealSave(ss.str());
}