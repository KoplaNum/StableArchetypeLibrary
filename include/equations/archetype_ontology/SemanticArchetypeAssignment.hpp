#ifndef SEMANTIC_ARCHETYPE_ASSIGNMENT_HPP
#define SEMANTIC_ARCHETYPE_ASSIGNMENT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SemanticArchetypeAssignment {

constexpr int EQUATION_NUMBER = 5;
constexpr const char* TITLE = "Archetype Semantic Types";
constexpr const char* LATEX = R"(\mathcal{A}_1 \sim \text{order}, \mathcal{A}_2 \sim \text{turbulence}, \mathcal{A}_3 \sim \text{growth}, \mathcal{A}_4 \sim \text{decay}, \mathcal{A}_5 \sim \text{balance})";
constexpr const char* MEANING = "Each archetype encodes a distinct visual semantic mode";
constexpr const char* CODE_ROLE = "Defines archetype semantic identifiers";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {1, 2};
constexpr int DOWNSTREAM_DEPS[] = {71, 72, 73, 74, 75};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 5;

// ArchetypeType aliases (defined in StableArchetypeCommon.hpp)
// ARCHE_ORDER = 0, ARCHE_TURBULENCE = 1, ARCHE_GROWTH = 2, ARCHE_DECAY = 3, ARCHE_BALANCE = 4

inline const char* get_archetype_name(int k) {
    static const char* names[] = {"order", "turbulence", "growth", "decay", "balance"};
    return (k >= 0 && k < K_ARCHETYPES) ? names[k] : "unknown";
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
