#ifndef MIXINGWEIGHTFROMENTROPY_HPP
#define MIXINGWEIGHTFROMENTROPY_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace MixingWeightFromEntropy {

constexpr int EQUATION_NUMBER = 66;
constexpr const char* TITLE = "Mixing Weight from Entropy";
constexpr const char* LATEX = R"(\lambda_t = \sigma\!\left( a_\lambda H_\pi(t) + b_\lambda \right))";
constexpr const char* MEANING = "Entropy determines hard/soft blend ratio";
constexpr const char* CODE_ROLE = "Computes mixing parameter from gating entropy";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {58};
constexpr int DOWNSTREAM_DEPS[] = {65};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

inline float compute_lambda(float H, float a=2.0f, float b=-1.0f) {
    return sigmoid(a * H + b);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
