#ifndef MODULATEDTRENDINPUT_HPP
#define MODULATEDTRENDINPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace ModulatedTrendInput {

constexpr int EQUATION_NUMBER = 34;
constexpr const char* TITLE = "Modulated Trend Input";
constexpr const char* LATEX = R"(\tilde{c}_{p,t}^{(\tau)} = \operatorname{clip}\!\left( c_t^{(\tau)} + \alpha_\tau \sin(2x_p - 1.5y_p + \lambda_\tau t), -1,1 \right))";
constexpr const char* MEANING = "Trend with diagonal spatial pattern";
constexpr const char* CODE_ROLE = "Computes trend component of pixel input";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {24};
constexpr int DOWNSTREAM_DEPS[] = {31};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float modulate_trend(float c, float x, float y, float phase) {
    float raw = c + 0.15f * sinf(2.0f * x - 1.5f * y + phase);
    return clampf(raw, -1.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
