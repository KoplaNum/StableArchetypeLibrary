#ifndef REDCHANNELSYNTHESIS_HPP
#define REDCHANNELSYNTHESIS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace RedChannelSynthesis {

constexpr int EQUATION_NUMBER = 92;
constexpr const char* TITLE = "Red Channel Synthesis";
constexpr const char* LATEX = R"(R_{p,t} = \operatorname{clip}\!\left( 0.70\,o_{p,t}^{(R)} + 0.30\,s_{p,t}, 0, 1 \right) v_p)";
constexpr const char* MEANING = "Red output from blended red and stripe, scaled by vignette";
constexpr const char* CODE_ROLE = "Computes final red channel per pixel";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {19, 45, 61, 91};
constexpr int DOWNSTREAM_DEPS[] = {95, 96};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float compute_red(float o_r, float stripe, float vignette) {
    return clampf(0.70f * o_r + 0.30f * stripe, 0.0f, 1.0f) * vignette;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
