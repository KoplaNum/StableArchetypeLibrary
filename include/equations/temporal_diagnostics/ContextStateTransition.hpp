#ifndef CONTEXTSTATETRANSITION_HPP
#define CONTEXTSTATETRANSITION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ContextStateTransition {

constexpr int EQUATION_NUMBER = 81;
constexpr const char* TITLE = "Context State Transition";
constexpr const char* LATEX = R"(\mathbf{c}_{t+1} = F(\mathbf{c}_t,\eta_t,\bar{w}_{1,t},\bar{w}_{2,t}))";
constexpr const char* MEANING = "Context evolves via deterministic dynamics plus noise";
constexpr const char* CODE_ROLE = "Defines context update function";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 26, 27, 29};
constexpr int DOWNSTREAM_DEPS[] = {82, 85};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
