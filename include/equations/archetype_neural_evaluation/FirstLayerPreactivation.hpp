#ifndef FIRSTLAYERPREACTIVATION_HPP
#define FIRSTLAYERPREACTIVATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace FirstLayerPreactivation {

constexpr int EQUATION_NUMBER = 41;
constexpr const char* TITLE = "First Layer Pre-activation";
constexpr const char* LATEX = R"(\mathbf{h}_{k,p,t}^{(1)} = W_k^{(1)} \mathbf{z}_{p,t} + b_k^{(1)})";
constexpr const char* MEANING = "Linear transformation of input by first layer weights";
constexpr const char* CODE_ROLE = "Computes hidden layer 1 pre-activation per archetype";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {3, 7, 9, 10, 12, 31};
constexpr int DOWNSTREAM_DEPS[] = {42};

constexpr int NUM_UPSTREAM = 6;
constexpr int NUM_DOWNSTREAM = 1;

inline void compute_h1(float* out, float* W1, float* b1, float* z, int d_in, int d_h) {
    for(int j=0; j<d_h; j++) {
        float acc = b1[j];
        for(int i=0; i<d_in; i++) {
            acc += z[i] * W1[j * d_in + i];
        }
        out[j] = acc;
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
