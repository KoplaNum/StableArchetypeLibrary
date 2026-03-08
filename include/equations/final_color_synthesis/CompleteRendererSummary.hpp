#ifndef COMPLETERENDERERSUMMARY_HPP
#define COMPLETERENDERERSUMMARY_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace CompleteRendererSummary {

constexpr int EQUATION_NUMBER = 100;
constexpr const char* TITLE = "Complete Renderer Summary";
constexpr const char* LATEX = R"(\boxed{\mathbf{I}_{p,t} = \Psi\!\left( p,\mathbf{c}_t,\boldsymbol{\pi}(t),\{\Theta_k\}_{k=1}^{K} \right)})";
constexpr const char* MEANING = "Full renderer as context-conditioned archetype-blended neural field";
constexpr const char* CODE_ROLE = "Summarizes entire rendering pipeline";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL/OpenGL";

constexpr int UPSTREAM_DEPS[] = {21, 53, 61, 95};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
