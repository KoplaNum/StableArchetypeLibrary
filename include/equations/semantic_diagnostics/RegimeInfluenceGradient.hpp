#ifndef REGIMEINFLUENCEGRADIENT_HPP
#define REGIMEINFLUENCEGRADIENT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace RegimeInfluenceGradient {

constexpr int EQUATION_NUMBER = 76;
constexpr const char* TITLE = "Regime Influence Gradient";
constexpr const char* LATEX = R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(r)}} = \sum_{k=1}^{K}\frac{\partial \pi_k(t)}{\partial c_t^{(r)}}\mathbf{o}_{k,p,t} + \sum_{k=1}^{K}\pi_k(t)\frac{\partial \mathbf{o}_{k,p,t}}{\partial c_t^{(r)}})";
constexpr const char* MEANING = "How regime context affects output via gating and direct paths";
constexpr const char* CODE_ROLE = "Computes regime sensitivity for diagnostics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 53, 61, 71};
constexpr int DOWNSTREAM_DEPS[] = {80};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
