#ifndef PROBABILITYNORMALIZATION_HPP
#define PROBABILITYNORMALIZATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ProbabilityNormalization {

constexpr int EQUATION_NUMBER = 54;
constexpr const char* TITLE = "Probability Normalization";
constexpr const char* LATEX = R"(\sum_{k=1}^{K}\pi_k(t) = 1)";
constexpr const char* MEANING = "Archetype weights form valid probability distribution";
constexpr const char* CODE_ROLE = "Validates softmax output normalization";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 53};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline bool validate_normalization(float* pi, int K, float tol=1e-5f) {
    float sum = 0.0f;
    for(int k=0; k<K; k++) sum += pi[k];
    float err = sum - 1.0f;
    return (err > -tol && err < tol);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
