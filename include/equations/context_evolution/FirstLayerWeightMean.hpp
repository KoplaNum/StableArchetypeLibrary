#ifndef FIRSTLAYERWEIGHTMEAN_HPP
#define FIRSTLAYERWEIGHTMEAN_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace FirstLayerWeightMean {

constexpr int EQUATION_NUMBER = 26;
constexpr const char* TITLE = "Layer 1 Mean Weight";
constexpr const char* LATEX = R"(\bar{w}_{1,t} = \frac{1}{|W^{(1)}|}\sum_{u} W^{(1)}_u(t))";
constexpr const char* MEANING = "Average of first layer weights";
constexpr const char* CODE_ROLE = "Computes mean of W1 weights";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {3};
constexpr int DOWNSTREAM_DEPS[] = {24, 28};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_mean_w1(float* W1, int size) {
    if(!W1 || size <= 0) return 0.0f;
    float sum = 0.0f;
    for(int i=0; i<size; i++) sum += W1[i];
    return sum / (float)size;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
