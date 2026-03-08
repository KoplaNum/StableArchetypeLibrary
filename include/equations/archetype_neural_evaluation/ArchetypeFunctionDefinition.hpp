#ifndef ARCHETYPEFUNCTIONDEFINITION_HPP
#define ARCHETYPEFUNCTIONDEFINITION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeFunctionDefinition {

constexpr int EQUATION_NUMBER = 47;
constexpr const char* TITLE = "Archetype Function Definition";
constexpr const char* LATEX = R"(\mathcal{A}_k(\mathbf{z}_{p,t};\Theta_k) = \mathbf{o}_{k,p,t})";
constexpr const char* MEANING = "Archetype k maps input to output given parameters";
constexpr const char* CODE_ROLE = "Defines archetype evaluation interface";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {3, 8, 44};
constexpr int DOWNSTREAM_DEPS[] = {48, 49, 61};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 3;

using ArchetypeEvalFunc = void(*)(float* out, float* W1, float* b1, float* W2, float* b2, float* z);

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
