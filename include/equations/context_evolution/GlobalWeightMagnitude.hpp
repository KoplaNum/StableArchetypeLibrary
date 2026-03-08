#ifndef GLOBALWEIGHTMAGNITUDE_HPP
#define GLOBALWEIGHTMAGNITUDE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace GlobalWeightMagnitude {

constexpr int EQUATION_NUMBER = 28;
constexpr const char* TITLE = "Mean Weight Magnitude";
constexpr const char* LATEX = R"(\bar{m}_t = \frac{1}{|W^{(1)}|}\sum_{u} |W^{(1)}_u(t)| + \frac{1}{|W^{(2)}|}\sum_{u} |W^{(2)}_u(t)|)";
constexpr const char* MEANING = "Sum of absolute weight means from both layers";
constexpr const char* CODE_ROLE = "Computes mean magnitude for volatility";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {26, 27};
constexpr int DOWNSTREAM_DEPS[] = {23};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline float compute_mean_magnitude(float* W1, int s1, float* W2, int s2) {
    float m1 = 0.0f, m2 = 0.0f;
    if(W1 && s1 > 0) {
        for(int i=0; i<s1; i++) m1 += fabsf(W1[i]);
        m1 /= (float)s1;
    }
    if(W2 && s2 > 0) {
        for(int i=0; i<s2; i++) m2 += fabsf(W2[i]);
        m2 /= (float)s2;
    }
    return m1 + m2;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
