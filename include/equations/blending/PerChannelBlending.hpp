#ifndef PERCHANNELBLENDING_HPP
#define PERCHANNELBLENDING_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace PerChannelBlending {

constexpr int EQUATION_NUMBER = 62;
constexpr const char* TITLE = "Per-Channel Blending";
constexpr const char* LATEX = R"(o_{p,t}^{(c)} = \sum_{k=1}^{K}\pi_k(t)o_{k,p,t}^{(c)})";
constexpr const char* MEANING = "Scalar blend equation for each color channel";
constexpr const char* CODE_ROLE = "Blends single color channel across archetypes";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {2, 45, 53, 61};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 0;

inline float blend_channel(float* o_k_c, float* pi, int K) {
    float sum = 0.0f;
    for(int k=0; k<K; k++) {
        sum += pi[k] * o_k_c[k];
    }
    return sum;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
