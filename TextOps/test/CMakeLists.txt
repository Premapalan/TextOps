cmake_minimum_required(VERSION 3.24)

project(test LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE textops_lib GTest::gtest_main)

message(STATUS "constructed path : ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_SOURCE_DIR}/rt.exe
    COMMENT "Copying test executable"
)

# --- Test discovery ---
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}
    PROPERTIES ENVIRONMENT "GTEST_COLOR=yes"  
)
