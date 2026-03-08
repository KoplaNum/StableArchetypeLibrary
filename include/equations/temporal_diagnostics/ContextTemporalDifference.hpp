#ifndef CONTEXTTEMPORALDIFFERENCE_HPP
#define CONTEXTTEMPORALDIFFERENCE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace ContextTemporalDifference {

constexpr int EQUATION_NUMBER = 85;
constexpr const char* TITLE = "Context Temporal Difference";
constexpr const char* LATEX = R"(\Delta_c(t) = \|\mathbf{c}_{t+1}-\mathbf{c}_t\|_2)";
constexpr const char* MEANING = "Euclidean change in context vector";
constexpr const char* CODE_ROLE = "Measures context temporal stability";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 81};
constexpr int DOWNSTREAM_DEPS[] = {86, 88};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_context_diff(float* c_curr, float* c_prev, int d_c) {
    float sum = 0.0f;
    for(int i=0; i<d_c; i++) {
        float d = c_curr[i] - c_prev[i];
        sum += d * d;
    }
    return sqrtf(sum);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
