add_executable(textops_bench
    bench.cpp
)

target_link_libraries(textops_bench PRIVATE
    textops_lib
    benchmark::benchmark_main
)