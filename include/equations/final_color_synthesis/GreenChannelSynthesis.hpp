#ifndef GREENCHANNELSYNTHESIS_HPP
#define GREENCHANNELSYNTHESIS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace GreenChannelSynthesis {

constexpr int EQUATION_NUMBER = 93;
constexpr const char* TITLE = "Green Channel Synthesis";
constexpr const char* LATEX = R"(G_{p,t} = \operatorname{clip}\!\left( 0.85\,o_{p,t}^{(G)} + 0.15\,(1-s_{p,t}), 0, 1 \right) v_p)";
constexpr const char* MEANING = "Green output from blended green and inverse stripe";
constexpr const char* CODE_ROLE = "Computes final green channel per pixel";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {19, 45, 61, 91};
constexpr int DOWNSTREAM_DEPS[] = {95, 96};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float compute_green(float o_g, float stripe, float vignette) {
    return clampf(0.85f * o_g + 0.15f * (1.0f - stripe), 0.0f, 1.0f) * vignette;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
