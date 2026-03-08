#ifndef RISKINFLUENCEGRADIENT_HPP
#define RISKINFLUENCEGRADIENT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace RiskInfluenceGradient {

constexpr int EQUATION_NUMBER = 79;
constexpr const char* TITLE = "Risk Influence Gradient";
constexpr const char* LATEX = R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(\rho)}} = \sum_{k=1}^{K}\frac{\partial \pi_k(t)}{\partial c_t^{(\rho)}}\mathbf{o}_{k,p,t} + \sum_{k=1}^{K}\pi_k(t)\frac{\partial \mathbf{o}_{k,p,t}}{\partial c_t^{(\rho)}})";
constexpr const char* MEANING = "How risk context affects output";
constexpr const char* CODE_ROLE = "Computes risk sensitivity for diagnostics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 53, 61, 74};
constexpr int DOWNSTREAM_DEPS[] = {80};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
