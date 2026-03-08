#ifndef GATINGSTABILITYBOUND_HPP
#define GATINGSTABILITYBOUND_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace GatingStabilityBound {

constexpr int EQUATION_NUMBER = 87;
constexpr const char* TITLE = "Gating Stability Bound";
constexpr const char* LATEX = R"(\Delta_\pi(t) \le L_G \Delta_c(t))";
constexpr const char* MEANING = "Gating change bounded by context change";
constexpr const char* CODE_ROLE = "Defines controller Lipschitz constant";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {60, 85};
constexpr int DOWNSTREAM_DEPS[] = {88};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
