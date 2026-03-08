#ifndef TRENDSTATEDYNAMICS_HPP
#define TRENDSTATEDYNAMICS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace TrendStateDynamics {

constexpr int EQUATION_NUMBER = 24;
constexpr const char* TITLE = "Trend Dynamics";
constexpr const char* LATEX = R"(c_t^{(\tau)} = \tanh\!\left( a_\tau (\bar{w}_{2,t}-\bar{w}_{1,t}) + b_\tau \sin(\omega_\tau t) + \eta_t^{(\tau)} \right))";
constexpr const char* MEANING = "Trend from weight differential and oscillation";
constexpr const char* CODE_ROLE = "Computes trend from weight means and phase";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 26, 27, 29};
constexpr int DOWNSTREAM_DEPS[] = {25, 34};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_trend(float w1_mean, float w2_mean, float phase, float noise) {
    float inner = 1.4f * (w2_mean - w1_mean) + 0.5f * sinf(0.12f * phase + 1.3f) + 0.20f * noise;
    return tanhf(inner);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
