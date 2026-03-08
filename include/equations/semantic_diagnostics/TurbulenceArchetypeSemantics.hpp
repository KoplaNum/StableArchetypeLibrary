#ifndef TURBULENCEARCHETYPESEMANTICS_HPP
#define TURBULENCEARCHETYPESEMANTICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace TurbulenceArchetypeSemantics {

constexpr int EQUATION_NUMBER = 72;
constexpr const char* TITLE = "Turbulence Archetype Semantics";
constexpr const char* LATEX = R"(\mathcal{A}_2 : \mathbf{z}_{p,t} \mapsto \text{branching turbulent motifs})";
constexpr const char* MEANING = "Archetype 2 produces chaotic branching patterns";
constexpr const char* CODE_ROLE = "Documents turbulence archetype visual semantics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {5, 47};
constexpr int DOWNSTREAM_DEPS[] = {77};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
