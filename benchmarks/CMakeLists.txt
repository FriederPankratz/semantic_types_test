add_executable(sematic_benchmarks main.cpp bench_CerealEigen.cpp bench_CerealSemantic.cpp GenericTypeReadWrite.cpp)

target_link_libraries(sematic_benchmarks PRIVATE semantic_types)

target_include_directories(sematic_benchmarks PRIVATE
        ${CMAKE_CURRENT_PROJECT_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

install(TARGETS sematic_benchmarks
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows