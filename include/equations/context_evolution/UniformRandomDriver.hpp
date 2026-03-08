#ifndef UNIFORMRANDOMDRIVER_HPP
#define UNIFORMRANDOMDRIVER_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace UniformRandomDriver {

constexpr int EQUATION_NUMBER = 30;
constexpr const char* TITLE = "Unit Random Source";
constexpr const char* LATEX = R"(u_t^{(q)} \in [0,1])";
constexpr const char* MEANING = "Unit random from hash-based integer process";
constexpr const char* CODE_ROLE = "Generates unit random from seed mixing";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {29, 37};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 2;

inline unsigned int mix_u32(unsigned int x) {
    x ^= x >> 16;
    x *= 2246822519u;
    x ^= x >> 13;
    x *= 3266489917u;
    x ^= x >> 16;
    return x;
}

inline float u32_to_unit(unsigned int x) {
    return (float)(x & 0x00FFFFFFu) / 16777215.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
