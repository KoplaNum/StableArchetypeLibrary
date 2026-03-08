#ifndef OUTPUTTEMPORALDIFFERENCE_HPP
#define OUTPUTTEMPORALDIFFERENCE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace OutputTemporalDifference {

constexpr int EQUATION_NUMBER = 84;
constexpr const char* TITLE = "Output Temporal Difference";
constexpr const char* LATEX = R"(\Delta_o(t) = \frac{1}{|\Omega|}\sum_{p\in\Omega}\|\mathbf{o}_{p,t+1}-\mathbf{o}_{p,t}\|_2)";
constexpr const char* MEANING = "Average per-pixel output change between frames";
constexpr const char* CODE_ROLE = "Measures visual temporal stability";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {13, 61, 83};
constexpr int DOWNSTREAM_DEPS[] = {86, 88};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_output_diff(float* o_curr, float* o_prev, int N) {
    float sum = 0.0f;
    for(int p=0; p<N; p++) {
        float dr = o_curr[p*3+0] - o_prev[p*3+0];
        float dg = o_curr[p*3+1] - o_prev[p*3+1];
        float db = o_curr[p*3+2] - o_prev[p*3+2];
        sum += sqrtf(dr*dr + dg*dg + db*db);
    }
    return sum / (float)N;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
