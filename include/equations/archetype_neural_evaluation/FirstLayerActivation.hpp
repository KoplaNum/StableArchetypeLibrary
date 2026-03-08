#ifndef FIRSTLAYERACTIVATION_HPP
#define FIRSTLAYERACTIVATION_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace FirstLayerActivation {

constexpr int EQUATION_NUMBER = 42;
constexpr const char* TITLE = "First Layer Activation";
constexpr const char* LATEX = R"(\mathbf{a}_{k,p,t}^{(1)} = \tanh\!\left( \mathbf{h}_{k,p,t}^{(1)} \right))";
constexpr const char* MEANING = "Tanh nonlinearity applied to first layer";
constexpr const char* CODE_ROLE = "Applies tanh activation to hidden layer 1";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {12, 41};
constexpr int DOWNSTREAM_DEPS[] = {43};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline void apply_tanh(float* out, float* in, int size) {
    for(int i=0; i<size; i++) {
        out[i] = tanhf(in[i]);
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
