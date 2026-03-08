#ifndef GROWTHARCHETYPESEMANTICS_HPP
#define GROWTHARCHETYPESEMANTICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace GrowthArchetypeSemantics {

constexpr int EQUATION_NUMBER = 73;
constexpr const char* TITLE = "Growth Archetype Semantics";
constexpr const char* LATEX = R"(\mathcal{A}_3 : \mathbf{z}_{p,t} \mapsto \text{expansive growth motifs})";
constexpr const char* MEANING = "Archetype 3 produces outward expanding patterns";
constexpr const char* CODE_ROLE = "Documents growth archetype visual semantics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {5, 47};
constexpr int DOWNSTREAM_DEPS[] = {78};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
