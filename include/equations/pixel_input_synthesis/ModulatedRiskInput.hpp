#ifndef MODULATEDRISKINPUT_HPP
#define MODULATEDRISKINPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace ModulatedRiskInput {

constexpr int EQUATION_NUMBER = 35;
constexpr const char* TITLE = "Modulated Risk Input";
constexpr const char* LATEX = R"(\tilde{c}_{p,t}^{(\rho)} = \operatorname{clip}\!\left( c_t^{(\rho)} + \alpha_\rho \cos(3(x_p+y_p)-\lambda_\rho t), -1,1 \right))";
constexpr const char* MEANING = "Risk with diagonal cosine pattern";
constexpr const char* CODE_ROLE = "Computes risk component of pixel input";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {25};
constexpr int DOWNSTREAM_DEPS[] = {31};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float modulate_risk(float c, float x, float y, float phase) {
    float raw = c + 0.10f * cosf(3.0f * (x + y) - phase);
    return clampf(raw, -1.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
