#ifndef DECAYARCHETYPESEMANTICS_HPP
#define DECAYARCHETYPESEMANTICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace DecayArchetypeSemantics {

constexpr int EQUATION_NUMBER = 74;
constexpr const char* TITLE = "Decay Archetype Semantics";
constexpr const char* LATEX = R"(\mathcal{A}_4 : \mathbf{z}_{p,t} \mapsto \text{centered collapse motifs})";
constexpr const char* MEANING = "Archetype 4 produces inward collapsing patterns";
constexpr const char* CODE_ROLE = "Documents decay archetype visual semantics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {5, 47};
constexpr int DOWNSTREAM_DEPS[] = {79};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
