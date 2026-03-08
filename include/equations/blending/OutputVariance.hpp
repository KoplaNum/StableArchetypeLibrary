#ifndef OUTPUTVARIANCE_HPP
#define OUTPUTVARIANCE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OutputVariance {

constexpr int EQUATION_NUMBER = 70;
constexpr const char* TITLE = "Output Variance";
constexpr const char* LATEX = R"(\operatorname{Var}_t(\mathbf{o}) = \frac{1}{|\Omega|}\sum_{p\in\Omega}\|\mathbf{o}_{p,t}-\bar{\mathbf{o}}_t\|_2^2)";
constexpr const char* MEANING = "Spatial variance of blended output";
constexpr const char* CODE_ROLE = "Measures frame contrast/diversity";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {13, 61, 69};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 0;

inline float compute_variance(float* frame, float* mean, int W, int H) {
    int N = W * H;
    float var = 0.0f;
    for(int p=0; p<N; p++) {
        float dr = frame[p*3+0] - mean[0];
        float dg = frame[p*3+1] - mean[1];
        float db = frame[p*3+2] - mean[2];
        var += dr*dr + dg*dg + db*db;
    }
    return var / (float)N;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
