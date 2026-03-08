#ifndef GATINGCONFIDENCE_HPP
#define GATINGCONFIDENCE_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace GatingConfidence {

constexpr int EQUATION_NUMBER = 59;
constexpr const char* TITLE = "Gating Confidence";
constexpr const char* LATEX = R"(\operatorname{conf}(t) = 1 - \frac{H_\pi(t)}{\log K})";
constexpr const char* MEANING = "Normalized confidence in archetype selection";
constexpr const char* CODE_ROLE = "Computes selection certainty metric";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 58};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline float compute_confidence(float H, int K) {
    float logK = logf((float)K);
    if(logK < 1e-10f) return 1.0f;
    float conf = 1.0f - H / logK;
    return (conf < 0.0f) ? 0.0f : ((conf > 1.0f) ? 1.0f : conf);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
