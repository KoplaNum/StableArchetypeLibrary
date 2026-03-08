#ifndef ARCHETYPEOPERATORNOTATION_HPP
#define ARCHETYPEOPERATORNOTATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeOperatorNotation {

constexpr int EQUATION_NUMBER = 48;
constexpr const char* TITLE = "Archetype Operator Notation";
constexpr const char* LATEX = R"(\mathbf{o}_{k,p,t} = \Phi_k(\mathbf{z}_{p,t}))";
constexpr const char* MEANING = "Compact notation for archetype neural map";
constexpr const char* CODE_ROLE = "Defines operator alias for archetype";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {8, 47};
constexpr int DOWNSTREAM_DEPS[] = {50, 83};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 2;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
