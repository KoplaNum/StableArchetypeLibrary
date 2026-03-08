#ifndef OUTPUTACTIVATION_HPP
#define OUTPUTACTIVATION_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace OutputActivation {

constexpr int EQUATION_NUMBER = 44;
constexpr const char* TITLE = "Output Activation";
constexpr const char* LATEX = R"(\mathbf{o}_{k,p,t} = \frac{1}{2}\mathbf{1} + \frac{1}{2}\tanh\!\left( \mathbf{h}_{k,p,t}^{(2)} \right))";
constexpr const char* MEANING = "Scaled tanh maps output to [0,1] color range";
constexpr const char* CODE_ROLE = "Produces final archetype color output";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {11, 43};
constexpr int DOWNSTREAM_DEPS[] = {45, 46, 61, 62, 64};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 5;

inline void compute_output(float* out, float* h2, int d_out) {
    for(int k=0; k<d_out; k++) {
        float s = 0.5f + 0.5f * tanhf(h2[k]);
        out[k] = (s < 0.0f) ? 0.0f : ((s > 1.0f) ? 1.0f : s);
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
