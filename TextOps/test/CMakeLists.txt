cmake_minimum_required(VERSION 3.24)

project(test LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/test.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ../textops/src)
target_link_libraries(${PROJECT_NAME} PRIVATE textops)

message(STATUS "constructed path : ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/rt
    COMMENT "Creating symbolic link for the program"

)