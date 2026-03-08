#ifndef BLENDEDOUTPUT_HPP
#define BLENDEDOUTPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace BlendedOutput {

constexpr int EQUATION_NUMBER = 61;
constexpr const char* TITLE = "Blended Output";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t} = \sum_{k=1}^{K} \pi_k(t)\mathbf{o}_{k,p,t})";
constexpr const char* MEANING = "Weighted sum of all archetype outputs per pixel";
constexpr const char* CODE_ROLE = "Computes final blended color from archetypes";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {2, 7, 47, 53};
constexpr int DOWNSTREAM_DEPS[] = {62, 63, 64, 69, 70, 92, 93, 94};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 8;

inline void blend_outputs(float* out, float** o_k, float* pi, int K, int d_o) {
    for(int c=0; c<d_o; c++) out[c] = 0.0f;
    for(int k=0; k<K; k++) {
        for(int c=0; c<d_o; c++) {
            out[c] += pi[k] * o_k[k][c];
        }
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
