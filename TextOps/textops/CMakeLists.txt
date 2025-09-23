cmake_minimum_required(VERSION 3.24)

project(textops LANGUAGES CXX)

add_library(${PROJECT_NAME}
    src/Msg.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC pugixml fmt::fmt tl::expected)