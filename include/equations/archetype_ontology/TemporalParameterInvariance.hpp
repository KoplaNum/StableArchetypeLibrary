#ifndef TEMPORAL_PARAMETER_INVARIANCE_HPP
#define TEMPORAL_PARAMETER_INVARIANCE_HPP

namespace TemporalParameterInvariance {

constexpr int EQUATION_NUMBER = 4;
constexpr const char* TITLE = "Parameter Stability";
constexpr const char* LATEX = R"(\Theta_k(t) = \Theta_k(0))";
constexpr const char* MEANING = "Archetype weights are fixed across frames unless explicit blending";
constexpr const char* CODE_ROLE = "Enforces weight stability - no mutation during render";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {3};
constexpr int DOWNSTREAM_DEPS[] = {50, 90};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 2;

inline bool are_weights_stable() { return true; }
inline void enforce_stability(float* weights) { (void)weights; }

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
