#ifndef MIXEDSELECTIONMODE_HPP
#define MIXEDSELECTIONMODE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace MixedSelectionMode {

constexpr int EQUATION_NUMBER = 65;
constexpr const char* TITLE = "Mixed Selection Mode";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t}^{\text{mix}} = (1-\lambda_t)\mathbf{o}_{k_t^\star,p,t} + \lambda_t\sum_{k=1}^{K}\pi_k(t)\mathbf{o}_{k,p,t})";
constexpr const char* MEANING = "Interpolation between hard and soft selection";
constexpr const char* CODE_ROLE = "Blends hard and soft modes continuously";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {53, 57, 61, 66};
constexpr int DOWNSTREAM_DEPS[] = {67, 68};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

inline void mixed_output(float* out, float* o_hard, float* o_soft, float lambda) {
    for(int c=0; c<3; c++) {
        out[c] = (1.0f - lambda) * o_hard[c] + lambda * o_soft[c];
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
