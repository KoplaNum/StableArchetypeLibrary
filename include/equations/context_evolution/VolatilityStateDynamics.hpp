#ifndef VOLATILITYSTATEDYNAMICS_HPP
#define VOLATILITYSTATEDYNAMICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace VolatilityStateDynamics {

constexpr int EQUATION_NUMBER = 23;
constexpr const char* TITLE = "Volatility Dynamics";
constexpr const char* LATEX = R"(c_t^{(v)} = \operatorname{clip}\!\left( a_v + b_v \bar{m}_t + \eta_t^{(v)}, -1, 1 \right))";
constexpr const char* MEANING = "Volatility driven by mean weight magnitude plus noise";
constexpr const char* CODE_ROLE = "Computes volatility from weight statistics";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 28, 29};
constexpr int DOWNSTREAM_DEPS[] = {25, 33, 56};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 3;

inline float clampf(float x, float lo, float hi) {
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

inline float compute_volatility(float mean_mag, float noise, float av=0.5f, float bv=0.8f) {
    return clampf(av + bv * mean_mag + 0.15f * noise, -1.0f, 1.0f);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
