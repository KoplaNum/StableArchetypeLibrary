#ifndef SECONDLAYERPREACTIVATION_HPP
#define SECONDLAYERPREACTIVATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SecondLayerPreactivation {

constexpr int EQUATION_NUMBER = 43;
constexpr const char* TITLE = "Second Layer Pre-activation";
constexpr const char* LATEX = R"(\mathbf{h}_{k,p,t}^{(2)} = W_k^{(2)} \mathbf{a}_{k,p,t}^{(1)} + b_k^{(2)})";
constexpr const char* MEANING = "Linear transformation from hidden to output";
constexpr const char* CODE_ROLE = "Computes output layer pre-activation per archetype";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {3, 7, 11, 12, 42};
constexpr int DOWNSTREAM_DEPS[] = {44};

constexpr int NUM_UPSTREAM = 5;
constexpr int NUM_DOWNSTREAM = 1;

inline void compute_h2(float* out, float* W2, float* b2, float* a, int d_h, int d_out) {
    for(int k=0; k<d_out; k++) {
        float acc = b2[k];
        for(int j=0; j<d_h; j++) {
            acc += a[j] * W2[k * d_h + j];
        }
        out[k] = acc;
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
