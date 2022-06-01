# /usr/bin/python3
import os
from conans import ConanFile, CMake, tools


class Traact(ConanFile):
    name = "semantic_types_test"
    version = "0.0.1"    

    description = ""
    url = "https://github.com/FriederPankratz/semantic_types_test"
    license = "MIT"
    author = "Frieder Pankratz"
    
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"
    compiler = "cppstd"
    options = {
        "shared": [True, False],
    }

    default_options = {
        "shared": True,
    }

    exports_sources = "CMakeLists.txt", "src/", "tests/", "benchmarks/"

    def requirements(self):        
        self.requires("benchmark/1.6.1")
        self.requires("gtest/1.10.0")
        self.requires("spdlog/1.8.2")
        self.requires("opencv/4.5.0@camposs/stable")
        self.requires("eigen/3.3.9@camposs/stable")
        self.requires("cereal/1.3.1")
        self.requires("nlohmann_json/3.10.5")


    def configure(self):
        self.options['spdlog'].shared = self.options.shared
        self.options['opencv'].shared = self.options.shared
        self.options['opencv'].with_cuda = True

        if self.settings.os == "Linux":
            self.options['opencv'].with_gtk = True





