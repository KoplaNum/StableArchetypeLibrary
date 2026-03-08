#ifndef ORDERARCHETYPESEMANTICS_HPP
#define ORDERARCHETYPESEMANTICS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OrderArchetypeSemantics {

constexpr int EQUATION_NUMBER = 71;
constexpr const char* TITLE = "Order Archetype Semantics";
constexpr const char* LATEX = R"(\mathcal{A}_1 : \mathbf{z}_{p,t} \mapsto \text{ordered geometric motifs})";
constexpr const char* MEANING = "Archetype 1 produces structured geometric patterns";
constexpr const char* CODE_ROLE = "Documents order archetype visual semantics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {5, 47};
constexpr int DOWNSTREAM_DEPS[] = {76};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
