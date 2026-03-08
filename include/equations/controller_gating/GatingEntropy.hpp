#ifndef GATINGENTROPY_HPP
#define GATINGENTROPY_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace GatingEntropy {

constexpr int EQUATION_NUMBER = 58;
constexpr const char* TITLE = "Gating Entropy";
constexpr const char* LATEX = R"(H_\pi(t) = -\sum_{k=1}^{K}\pi_k(t)\log \pi_k(t))";
constexpr const char* MEANING = "Shannon entropy of archetype distribution";
constexpr const char* CODE_ROLE = "Measures controller uncertainty/diversity";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 53};
constexpr int DOWNSTREAM_DEPS[] = {59, 66};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_entropy(float* pi, int K) {
    float H = 0.0f;
    for(int k=0; k<K; k++) {
        if(pi[k] > 1e-10f) {
            H -= pi[k] * logf(pi[k]);
        }
    }
    return H;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
