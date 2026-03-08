#ifndef GATINGTEMPORALDIFFERENCE_HPP
#define GATINGTEMPORALDIFFERENCE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace GatingTemporalDifference {

constexpr int EQUATION_NUMBER = 60;
constexpr const char* TITLE = "Gating Temporal Difference";
constexpr const char* LATEX = R"(\Delta_\pi(t) = \|\boldsymbol{\pi}(t) - \boldsymbol{\pi}(t-1)\|_1)";
constexpr const char* MEANING = "L1 change in archetype weights between frames";
constexpr const char* CODE_ROLE = "Measures controller stability over time";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 53};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline float compute_pi_l1_diff(float* pi_curr, float* pi_prev, int K) {
    float diff = 0.0f;
    for(int k=0; k<K; k++) {
        float d = pi_curr[k] - pi_prev[k];
        diff += (d < 0) ? -d : d;
    }
    return diff;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
