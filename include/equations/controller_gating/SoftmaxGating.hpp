#ifndef SOFTMAXGATING_HPP
#define SOFTMAXGATING_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace SoftmaxGating {

constexpr int EQUATION_NUMBER = 53;
constexpr const char* TITLE = "Softmax Gating";
constexpr const char* LATEX = R"(\pi_k(t) = \frac{\exp(q_{k,t}/\tau_t)}{\sum_{\ell=1}^{K}\exp(q_{\ell,t}/\tau_t)})";
constexpr const char* MEANING = "Normalized archetype weights via temperature-scaled softmax";
constexpr const char* CODE_ROLE = "Computes archetype blending probabilities";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 52, 56};
constexpr int DOWNSTREAM_DEPS[] = {54, 55, 57, 58, 61, 62, 64, 65};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 8;

inline float softmax_step1(float* pi, float* q, float tau, int K) {
    float max_q = q[0];
    for(int k=1; k<K; k++) {
        if(q[k] > max_q) max_q = q[k];
    }
    float sum_exp = 0.0f;
    for(int k=0; k<K; k++) {
        pi[k] = expf((q[k] - max_q) / tau);
        sum_exp += pi[k];
    }
    return sum_exp;
}

inline void softmax_normalize(float* pi, float sum_exp, int K) {
    for(int k=0; k<K; k++) {
        pi[k] /= sum_exp;
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
