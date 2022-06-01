#include <gtest/gtest.h>
#include <iostream>
#include <cereal/archives/json.hpp>
#include <nlohmann/json.hpp>

#include <specific/CerealEigen.h>
#include "gtest_utils.h"

TEST(CerealEigen, Save) {
    using namespace test_utils;

    std::stringstream ss;


    Eigen::Affine3d pose = Eigen::Translation3d(exp_px,exp_py,exp_pz) * Eigen::Quaterniond(exp_rw,exp_rx,exp_ry,exp_rz);

    {
        cereal::JSONOutputArchive archive_(ss);
        archive_(pose);
    }

    TestCerealSave(ss.str());

}