#include <benchmark/benchmark.h>
#include "Msg.hpp"   // pulled in via textops_lib PUBLIC includes

// ── 1. Construction ───────────────────────────────────────
static void BM_MsgConstruction(benchmark::State& state) {
    for (auto _ : state) {
        textops::Msg<int, std::string> msg("Value: {val}, Name: {name}", 123, "Test");
        benchmark::DoNotOptimize(msg);
    }
}
BENCHMARK(BM_MsgConstruction);


// ── 2. ExtractFormatTags ──────────────────────────────────
static void BM_MsgExtractFormatTags(benchmark::State& state) {
    textops::Msg<int, std::string> msg("Id: {id}, Label: {label}", 42, "demo");

    for (auto _ : state) {
        auto tags = msg.extractFormatTags();
        benchmark::DoNotOptimize(tags);
    }
}
BENCHMARK(BM_MsgExtractFormatTags);


// ── 3. FormatMessage ──────────────────────────────────────
static void BM_MsgFormatMessage(benchmark::State& state) {
    textops::Msg<int, std::string> msg("A={a}, B={b}", 10, "xyz");

    for (auto _ : state) {
        auto out = msg.formatMessage();
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_MsgFormatMessage);


// ── 4. AssignParameterValue ───────────────────────────────
static void BM_MsgAssignAndFormat(benchmark::State& state) {
    for (auto _ : state) {
        textops::Msg<> msg("A={a}, B={b}");
        msg.assignParameterValue("a", 999);
        msg.assignParameterValue("b", "xyz");
        auto out = msg.formatMessage();
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_MsgAssignAndFormat);


// ── 5. AssignParameterOverride ────────────────────────────
static void BM_MsgAssignOverrideAndFormat(benchmark::State& state) {
    for (auto _ : state) {
        textops::Msg<int, std::string> msg("A={a}, B={b}", 10, "hello");
        msg.assignParameterValue("a", 999);
        msg.assignParameterValue("b", "xyz");
        auto out = msg.formatMessage();
        benchmark::DoNotOptimize(out);
    }
}
BENCHMARK(BM_MsgAssignOverrideAndFormat);


// ── 6. Scaling — format with many tags ───────────────────
static void BM_MsgFormatScaling(benchmark::State& state) {
    // builds a format string with N tags based on benchmark parameter
    std::string fmt;
    for (int i = 0; i < state.range(0); ++i)
        fmt += "{tag" + std::to_string(i) + "} ";

    for (auto _ : state) {
        textops::Msg<> msg(fmt);
        auto tags = msg.extractFormatTags();
        benchmark::DoNotOptimize(tags);
    }
}
BENCHMARK(BM_MsgFormatScaling)->Arg(1)->Arg(5)->Arg(20)->Arg(50);
BENCHMARK_MAIN();