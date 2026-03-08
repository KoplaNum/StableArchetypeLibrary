#ifndef SIGNEDNOISEFROMUNIT_HPP
#define SIGNEDNOISEFROMUNIT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SignedNoiseFromUnit {

constexpr int EQUATION_NUMBER = 36;
constexpr const char* TITLE = "Signed Noise from Unit";
constexpr const char* LATEX = R"(\xi_{p,t} = 2 \chi_{p,t} - 1)";
constexpr const char* MEANING = "Converts unit hash output to [-1,1] noise";
constexpr const char* CODE_ROLE = "Maps unit random to signed noise";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {37};
constexpr int DOWNSTREAM_DEPS[] = {32, 33};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 2;

inline float unit_to_signed(float u) {
    return 2.0f * u - 1.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
