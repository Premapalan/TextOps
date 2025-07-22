cmake_minimum_required(VERSION 3.15)

project(textops LANGUAGES CXX)

target_link_libraries(${PROJECT_NAME} PUBLIC pugixml fmt::fmt tl::expected)