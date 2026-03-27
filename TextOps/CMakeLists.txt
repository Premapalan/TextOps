cmake_minimum_required(VERSION 3.24)
project(textops)

set(CMAKE_CXX_STANDARD 20)

#fmt
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG master
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(fmt)

#pugixml
include(FetchContent)
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG master
)
FetchContent_MakeAvailable(pugixml)
FetchContent_GetProperties(pugixml)
if(NOT pugixml_POPULATED)
    FetchContent_Populate(pugixml)
    add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
endif()

#tl::expected
include(FetchContent)
FetchContent_Declare(
    tl_expected
    GIT_REPOSITORY https://github.com/TartanLlama/expected.git
    GIT_TAG master
)
FetchContent_MakeAvailable(tl_expected)

# gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main      # Or set a specific release/tag
)
FetchContent_MakeAvailable(googletest)

# --- Google Benchmark ---
set(BENCHMARK_ENABLE_TESTING        OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS    OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_PERF_COUNTERS  OFF CACHE BOOL "" FORCE)
set(BENCHMARK_INSTALL_DOCS          OFF CACHE BOOL "" FORCE)
set(BENCHMARK_USE_BUNDLED_GTEST     OFF CACHE BOOL "" FORCE)  # use your existing GTest

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.9.1
)
FetchContent_MakeAvailable(benchmark)

target_compile_options(benchmark       PRIVATE -w)
target_compile_options(benchmark_main  PRIVATE -w)

add_subdirectory(textops_lib)
add_subdirectory(bench)
add_subdirectory(test)
