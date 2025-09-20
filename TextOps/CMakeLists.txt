cmake_minimum_required(VERSION 3.24)
project(extops)

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

add_subdirectory(textops)
add_subdirectory(test)
