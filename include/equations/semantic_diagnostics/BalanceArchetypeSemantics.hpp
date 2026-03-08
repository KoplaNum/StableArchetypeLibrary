#ifndef BALANCEARCHETYPESEMANTICS_HPP
#define BALANCEARCHETYPESEMANTICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace BalanceArchetypeSemantics {

constexpr int EQUATION_NUMBER = 75;
constexpr const char* TITLE = "Balance Archetype Semantics";
constexpr const char* LATEX = R"(\mathcal{A}_5 : \mathbf{z}_{p,t} \mapsto \text{balanced harmonic motifs})";
constexpr const char* MEANING = "Archetype 5 produces harmonious balanced patterns";
constexpr const char* CODE_ROLE = "Documents balance archetype visual semantics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {5, 47};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
