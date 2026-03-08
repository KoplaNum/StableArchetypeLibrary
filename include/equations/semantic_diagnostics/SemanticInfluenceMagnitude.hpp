#ifndef SEMANTICINFLUENCEMAGNITUDE_HPP
#define SEMANTICINFLUENCEMAGNITUDE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace SemanticInfluenceMagnitude {

constexpr int EQUATION_NUMBER = 80;
constexpr const char* TITLE = "Semantic Influence Magnitude";
constexpr const char* LATEX = R"(\mathcal{M}_{q}(t) = \frac{1}{|\Omega|}\sum_{p\in\Omega}\left\| \frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(q)}} \right\|_2)";
constexpr const char* MEANING = "Average sensitivity of output to context channel q";
constexpr const char* CODE_ROLE = "Measures semantic influence strength per context dimension";
constexpr const char* SUBSYSTEM = "semantic_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {13, 76, 77, 78, 79};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 5;
constexpr int NUM_DOWNSTREAM = 0;

inline float compute_influence_magnitude(float* grads, int N) {
    float sum = 0.0f;
    for(int p=0; p<N; p++) {
        float gx = grads[p*3+0];
        float gy = grads[p*3+1];
        float gz = grads[p*3+2];
        sum += sqrtf(gx*gx + gy*gy + gz*gz);
    }
    return sum / (float)N;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
