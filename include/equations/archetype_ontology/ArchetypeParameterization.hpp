#ifndef ARCHETYPE_PARAMETERIZATION_HPP
#define ARCHETYPE_PARAMETERIZATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeParameterization {

constexpr int EQUATION_NUMBER = 3;
constexpr const char* TITLE = "Archetype Parameter Structure";
constexpr const char* LATEX = R"(\Theta_k = \left( W_k^{(1)}, b_k^{(1)}, W_k^{(2)}, b_k^{(2)} \right))";
constexpr const char* MEANING = "Each archetype has two-layer MLP weights and biases";
constexpr const char* CODE_ROLE = "Defines parameter structure per archetype";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {1, 2};
constexpr int DOWNSTREAM_DEPS[] = {4, 7, 41, 43};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 4;

struct ArchetypeParameters {
    float* W1;
    float* b1;
    float* W2;
    float* b2;
    int archetype_id;
    
    inline bool validate() const {
        return W1 && b1 && W2 && b2 && 
               archetype_id >= 0 && archetype_id < K_ARCHETYPES;
    }
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
