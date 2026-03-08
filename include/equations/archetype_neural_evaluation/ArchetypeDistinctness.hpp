#ifndef ARCHETYPEDISTINCTNESS_HPP
#define ARCHETYPEDISTINCTNESS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeDistinctness {

constexpr int EQUATION_NUMBER = 49;
constexpr const char* TITLE = "Archetype Distinctness";
constexpr const char* LATEX = R"(\Phi_k \neq \Phi_\ell \quad \text{for } k \neq \ell)";
constexpr const char* MEANING = "Different archetypes produce different visual semantics";
constexpr const char* CODE_ROLE = "Asserts archetype diversity";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {47};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 0;

inline bool archetypes_distinct(float* params1, float* params2, int size) {
    if(!params1 || !params2) return false;
    float diff = 0.0f;
    for(int i=0; i<size; i++) {
        float d = params1[i] - params2[i];
        diff += d * d;
    }
    return diff > 1e-6f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
