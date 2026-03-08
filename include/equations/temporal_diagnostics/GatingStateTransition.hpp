#ifndef GATINGSTATETRANSITION_HPP
#define GATINGSTATETRANSITION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace GatingStateTransition {

constexpr int EQUATION_NUMBER = 82;
constexpr const char* TITLE = "Gating State Transition";
constexpr const char* LATEX = R"(\boldsymbol{\pi}(t+1) = G(\mathbf{c}_{t+1}))";
constexpr const char* MEANING = "Gating updates deterministically from new context";
constexpr const char* CODE_ROLE = "Defines gating update from context";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {51, 53, 81};
constexpr int DOWNSTREAM_DEPS[] = {83};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
