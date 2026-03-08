#ifndef VOLATILITYINFLUENCEGRADIENT_HPP
#define VOLATILITYINFLUENCEGRADIENT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace VolatilityInfluenceGradient {

constexpr int EQUATION_NUMBER = 77;
constexpr const char* TITLE = "Volatility Influence Gradient";
constexpr const char* LATEX = R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(v)}} = \sum_{k=1}^{K}\frac{\partial \pi_k(t)}{\partial c_t^{(v)}}\mathbf{o}_{k,p,t} + \sum_{k=1}^{K}\pi_k(t)\frac{\partial \mathbf{o}_{k,p,t}}{\partial c_t^{(v)}})";
constexpr const char* MEANING = "How volatility context affects output";
constexpr const char* CODE_ROLE = "Computes volatility sensitivity for diagnostics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 53, 61, 72};
constexpr int DOWNSTREAM_DEPS[] = {80};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
