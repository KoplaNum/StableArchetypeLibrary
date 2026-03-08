#ifndef MODULATEDVOLATILITYINPUT_HPP
#define MODULATEDVOLATILITYINPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace ModulatedVolatilityInput {

constexpr int EQUATION_NUMBER = 33;
constexpr const char* TITLE = "Modulated Volatility Input";
constexpr const char* LATEX = R"(\tilde{c}_{p,t}^{(v)} = \operatorname{clip}\!\left( c_t^{(v)} + \alpha_v |\xi_{p,t}| + \beta_v \cos(\lambda_v t + 4y_p), -1,1 \right))";
constexpr const char* MEANING = "Volatility with absolute noise and y-modulation";
constexpr const char* CODE_ROLE = "Computes volatility component of pixel input";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {23, 36};
constexpr int DOWNSTREAM_DEPS[] = {31};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float modulate_volatility(float c, float noise, float y, float phase) {
    float raw = c + 0.25f * fabsf(noise) + 0.10f * cosf(phase + 4.0f * y);
    return clampf(raw, -1.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
