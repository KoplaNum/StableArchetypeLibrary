#ifndef PROBABILITYNONNEGATIVITY_HPP
#define PROBABILITYNONNEGATIVITY_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ProbabilityNonNegativity {

constexpr int EQUATION_NUMBER = 55;
constexpr const char* TITLE = "Probability Non-negativity";
constexpr const char* LATEX = R"(\pi_k(t) \ge 0)";
constexpr const char* MEANING = "All archetype weights are non-negative";
constexpr const char* CODE_ROLE = "Validates softmax output positivity";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 53};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline bool validate_nonnegative(float* pi, int K) {
    for(int k=0; k<K; k++) {
        if(pi[k] < 0.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
