cmake_minimum_required(VERSION 3.24)

project(textops_lib LANGUAGES CXX)

add_library(${PROJECT_NAME}
    src/Msg.cpp
)

target_include_directories(textops_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(${PROJECT_NAME} PUBLIC pugixml fmt::fmt tl::expected)
