add_executable(sematic_tests main.cpp test_CerealEigen.cpp test_CerealSemantic.cpp gtest_utils.h gtest_utils.cpp)

target_link_libraries(sematic_tests PRIVATE semantic_types)

target_include_directories(sematic_benchmarks PRIVATE
        ${CMAKE_CURRENT_PROJECT_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

install(TARGETS sematic_tests
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows