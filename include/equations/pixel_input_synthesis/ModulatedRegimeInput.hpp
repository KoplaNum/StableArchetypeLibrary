#ifndef MODULATEDREGIMEINPUT_HPP
#define MODULATEDREGIMEINPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace ModulatedRegimeInput {

constexpr int EQUATION_NUMBER = 32;
constexpr const char* TITLE = "Modulated Regime Input";
constexpr const char* LATEX = R"(\tilde{c}_{p,t}^{(r)} = \operatorname{clip}\!\left( c_t^{(r)} + \alpha_r \xi_{p,t} + \beta_r \sin(\lambda_r t + 3x_p), -1,1 \right))";
constexpr const char* MEANING = "Regime with pixel noise and spatial modulation";
constexpr const char* CODE_ROLE = "Computes regime component of pixel input";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {22, 36};
constexpr int DOWNSTREAM_DEPS[] = {31};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float modulate_regime(float c, float noise, float x, float phase) {
    float raw = c + 0.20f * noise + 0.15f * sinf(phase + 3.0f * x);
    return clampf(raw, -1.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
