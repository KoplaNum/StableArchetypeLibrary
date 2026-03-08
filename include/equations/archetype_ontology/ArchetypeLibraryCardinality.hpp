#ifndef ARCHETYPE_LIBRARY_CARDINALITY_HPP
#define ARCHETYPE_LIBRARY_CARDINALITY_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeLibraryCardinality {

constexpr int EQUATION_NUMBER = 2;
constexpr const char* TITLE = "Archetype Count";
constexpr const char* LATEX = R"(K = |\mathfrak{A}|)";
constexpr const char* MEANING = "K is the cardinality of the archetype library";
constexpr const char* CODE_ROLE = "Defines the constant K_ARCHETYPES = 5";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {1};
constexpr int DOWNSTREAM_DEPS[] = {3, 53, 54, 55, 57, 58, 59, 61, 62, 64, 65, 66};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 12;

inline int get_archetype_count() { return K_ARCHETYPES; }
inline bool validate_count(int k) { return k == K_ARCHETYPES && k > 0; }

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
