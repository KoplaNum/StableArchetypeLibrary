#ifndef ARCHETYPEIDENTITYPERSISTENCE_HPP
#define ARCHETYPEIDENTITYPERSISTENCE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ArchetypeIdentityPersistence {

constexpr int EQUATION_NUMBER = 90;
constexpr const char* TITLE = "Archetype Identity Persistence";
constexpr const char* LATEX = R"(\text{stable archetypes} \implies \text{persistent symbolic identity across frames})";
constexpr const char* MEANING = "Fixed archetype weights preserve visual vocabulary";
constexpr const char* CODE_ROLE = "Documents archetype stability guarantee";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {4, 50};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
