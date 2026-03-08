#ifndef STRIPEMODULATIONPATTERN_HPP
#define STRIPEMODULATIONPATTERN_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace StripeModulationPattern {

constexpr int EQUATION_NUMBER = 91;
constexpr const char* TITLE = "Stripe Modulation Pattern";
constexpr const char* LATEX = R"(s_{p,t} = \frac{1}{2} + \frac{1}{2}\sin\!\left( 10(x_p+y_p) + \omega_s t + 2\xi_{p,t} \right))";
constexpr const char* MEANING = "Diagonal stripe pattern with temporal and noise modulation";
constexpr const char* CODE_ROLE = "Computes stripe factor for color synthesis";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15, 36};
constexpr int DOWNSTREAM_DEPS[] = {92, 93};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_stripe(float x, float y, float phase, float noise) {
    return 0.5f + 0.5f * sinf(10.0f * (x + y) + phase + 2.0f * noise);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
