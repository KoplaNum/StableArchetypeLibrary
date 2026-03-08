#ifndef BLUECHANNELSYNTHESIS_HPP
#define BLUECHANNELSYNTHESIS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace BlueChannelSynthesis {

constexpr int EQUATION_NUMBER = 94;
constexpr const char* TITLE = "Blue Channel Synthesis";
constexpr const char* LATEX = R"(B_{p,t} = \operatorname{clip}\!\left( 0.75\,o_{p,t}^{(B)} + 0.25\left(\frac{1}{2} + \frac{1}{2}\cos(8x_p-\omega_b t)\right), 0, 1 \right))";
constexpr const char* MEANING = "Blue output from blended blue and horizontal cosine";
constexpr const char* CODE_ROLE = "Computes final blue channel per pixel";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 45, 61};
constexpr int DOWNSTREAM_DEPS[] = {95, 96};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 2;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float compute_blue(float o_b, float x, float phase) {
    float cos_term = 0.5f + 0.5f * cosf(8.0f * x - phase);
    return clampf(0.75f * o_b + 0.25f * cos_term, 0.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
