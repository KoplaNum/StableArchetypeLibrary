#ifndef OUTPUTSTABILITYBOUND_HPP
#define OUTPUTSTABILITYBOUND_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OutputStabilityBound {

constexpr int EQUATION_NUMBER = 86;
constexpr const char* TITLE = "Output Stability Bound";
constexpr const char* LATEX = R"(\Delta_o(t) \le L_\Phi \Delta_c(t) + L_\pi \Delta_\pi(t))";
constexpr const char* MEANING = "Output change bounded by context and gating changes";
constexpr const char* CODE_ROLE = "Defines Lipschitz stability relationship";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {60, 84, 85};
constexpr int DOWNSTREAM_DEPS[] = {88, 89};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 2;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
