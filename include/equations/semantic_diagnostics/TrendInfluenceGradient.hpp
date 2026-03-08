#ifndef TRENDINFLUENCEGRADIENT_HPP
#define TRENDINFLUENCEGRADIENT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace TrendInfluenceGradient {

constexpr int EQUATION_NUMBER = 78;
constexpr const char* TITLE = "Trend Influence Gradient";
constexpr const char* LATEX = R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(\tau)}} = \sum_{k=1}^{K}\frac{\partial \pi_k(t)}{\partial c_t^{(\tau)}}\mathbf{o}_{k,p,t} + \sum_{k=1}^{K}\pi_k(t)\frac{\partial \mathbf{o}_{k,p,t}}{\partial c_t^{(\tau)}})";
constexpr const char* MEANING = "How trend context affects output";
constexpr const char* CODE_ROLE = "Computes trend sensitivity for diagnostics";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 53, 61, 73};
constexpr int DOWNSTREAM_DEPS[] = {80};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
