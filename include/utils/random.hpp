#pragma once
#include <random>

inline std::mt19937& global_rng() {
    static thread_local std::mt19937 rng{std::random_device{}()};
    return rng;
}