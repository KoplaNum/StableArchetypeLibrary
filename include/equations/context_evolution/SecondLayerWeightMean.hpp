#ifndef SECONDLAYERWEIGHTMEAN_HPP
#define SECONDLAYERWEIGHTMEAN_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SecondLayerWeightMean {

constexpr int EQUATION_NUMBER = 27;
constexpr const char* TITLE = "Layer 2 Mean Weight";
constexpr const char* LATEX = R"(\bar{w}_{2,t} = \frac{1}{|W^{(2)}|}\sum_{u} W^{(2)}_u(t))";
constexpr const char* MEANING = "Average of second layer weights";
constexpr const char* CODE_ROLE = "Computes mean of W2 weights";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {3};
constexpr int DOWNSTREAM_DEPS[] = {24, 28};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_mean_w2(float* W2, int size) {
    if(!W2 || size <= 0) return 0.0f;
    float sum = 0.0f;
    for(int i=0; i<size; i++) sum += W2[i];
    return sum / (float)size;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
