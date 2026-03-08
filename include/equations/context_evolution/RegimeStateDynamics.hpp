#ifndef REGIMESTATEDYNAMICS_HPP
#define REGIMESTATEDYNAMICS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace RegimeStateDynamics {

constexpr int EQUATION_NUMBER = 22;
constexpr const char* TITLE = "Regime Dynamics";
constexpr const char* LATEX = R"(c_t^{(r)} = \tanh\!\left( a_r \sin(\omega_r t) + b_r \cos(\nu_r t) + \eta_t^{(r)} \right))";
constexpr const char* MEANING = "Regime oscillates with dual frequencies plus noise";
constexpr const char* CODE_ROLE = "Computes regime from phase and noise";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 29};
constexpr int DOWNSTREAM_DEPS[] = {25, 32};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_regime(float phase, float noise, float ar=0.9f, float wr=0.31f, float br=0.6f, float vr=0.17f) {
    float inner = ar * sinf(wr * phase) + br * cosf(vr * phase) + 0.35f * noise;
    return tanhf(inner);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
