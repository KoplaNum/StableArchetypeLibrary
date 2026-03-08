#ifndef COMBINEDSTABILITYBOUND_HPP
#define COMBINEDSTABILITYBOUND_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace CombinedStabilityBound {

constexpr int EQUATION_NUMBER = 88;
constexpr const char* TITLE = "Combined Stability Bound";
constexpr const char* LATEX = R"(\Delta_o(t) \le (L_\Phi + L_\pi L_G)\Delta_c(t))";
constexpr const char* MEANING = "Output change ultimately bounded by context change";
constexpr const char* CODE_ROLE = "Defines end-to-end Lipschitz constant";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {86, 87};
constexpr int DOWNSTREAM_DEPS[] = {89};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
