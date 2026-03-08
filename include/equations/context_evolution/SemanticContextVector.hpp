#ifndef SEMANTICCONTEXTVECTOR_HPP
#define SEMANTICCONTEXTVECTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SemanticContextVector {

constexpr int EQUATION_NUMBER = 21;
constexpr const char* TITLE = "Context Vector Definition";
constexpr const char* LATEX = R"(\mathbf{c}_t = \begin{bmatrix} c_t^{(r)} \\ c_t^{(v)} \\ c_t^{(\tau)} \\ c_t^{(\rho)} \end{bmatrix} = \begin{bmatrix} \text{regime} \\ \text{volatility} \\ \text{trend} \\ \text{risk} \end{bmatrix}_t)";
constexpr const char* MEANING = "4D semantic context vector evolves per frame";
constexpr const char* CODE_ROLE = "Defines context structure (regime, volatility, trend, risk)";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {10};
constexpr int DOWNSTREAM_DEPS[] = {22, 23, 24, 25, 51, 52};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 6;

struct ContextVector {
    float regime;
    float volatility;
    float trend;
    float risk;
};

inline ContextVector make_context(float r, float v, float t, float rho) {
    ContextVector c = {r, v, t, rho};
    return c;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
