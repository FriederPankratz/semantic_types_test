#include "gtest_utils.h"

void TestCerealSave(const std::string& json_value) {
    using namespace test_utils;
    auto json = nlohmann::json::parse(json_value);

    EXPECT_DOUBLE_EQ(exp_px, json["value0"]["translation"]["x"].get<double>());
    EXPECT_DOUBLE_EQ(exp_py, json["value0"]["translation"]["y"].get<double>());
    EXPECT_DOUBLE_EQ(exp_pz, json["value0"]["translation"]["z"].get<double>());

    EXPECT_DOUBLE_EQ(exp_rx, json["value0"]["rotation"]["x"].get<double>());
    EXPECT_DOUBLE_EQ(exp_ry, json["value0"]["rotation"]["y"].get<double>());
    EXPECT_DOUBLE_EQ(exp_rz, json["value0"]["rotation"]["z"].get<double>());
    EXPECT_DOUBLE_EQ(exp_rw, json["value0"]["rotation"]["w"].get<double>());
}
