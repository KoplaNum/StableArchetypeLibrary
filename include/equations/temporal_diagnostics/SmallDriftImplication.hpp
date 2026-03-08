#ifndef SMALLDRIFTIMPLICATION_HPP
#define SMALLDRIFTIMPLICATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SmallDriftImplication {

constexpr int EQUATION_NUMBER = 89;
constexpr const char* TITLE = "Small Drift Implication";
constexpr const char* LATEX = R"(\text{small context drift} \implies \text{small visual drift})";
constexpr const char* MEANING = "Stable context produces stable visuals";
constexpr const char* CODE_ROLE = "Documents temporal stability guarantee";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {86, 88};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
