#ifndef RISKSTATEDYNAMICS_HPP
#define RISKSTATEDYNAMICS_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace RiskStateDynamics {

constexpr int EQUATION_NUMBER = 25;
constexpr const char* TITLE = "Risk Dynamics";
constexpr const char* LATEX = R"(c_t^{(\rho)} = \tanh\!\left( a_\rho c_t^{(r)} - b_\rho |c_t^{(v)}| + d_\rho c_t^{(\tau)} + \eta_t^{(\rho)} \right))";
constexpr const char* MEANING = "Risk combines regime, volatility, and trend";
constexpr const char* CODE_ROLE = "Computes risk from other context channels";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 22, 23, 24, 29};
constexpr int DOWNSTREAM_DEPS[] = {35};

constexpr int NUM_UPSTREAM = 5;
constexpr int NUM_DOWNSTREAM = 1;

inline float compute_risk(float regime, float volatility, float trend, float noise) {
    float raw = 0.8f * regime - 0.6f * fabsf(volatility) + 0.5f * trend + 0.15f * noise;
    return tanhf(raw);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
