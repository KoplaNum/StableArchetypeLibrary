#ifndef TEMPERATUREMODULATION_HPP
#define TEMPERATUREMODULATION_HPP

#include "../../common/StableArchetypeCommon.hpp"
#include <math.h>

namespace TemperatureModulation {

constexpr int EQUATION_NUMBER = 56;
constexpr const char* TITLE = "Temperature Modulation";
constexpr const char* LATEX = R"(\tau_t = \tau_{\min} + (\tau_{\max}-\tau_{\min}) \sigma\!\left(\gamma_\tau c_t^{(v)}\right))";
constexpr const char* MEANING = "Temperature varies with volatility via sigmoid";
constexpr const char* CODE_ROLE = "Computes adaptive softmax temperature";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {23};
constexpr int DOWNSTREAM_DEPS[] = {53};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

inline float compute_temperature(float volatility, float tau_min=0.5f, float tau_max=2.0f, float gamma=3.0f) {
    float sig = sigmoid(gamma * volatility);
    return tau_min + (tau_max - tau_min) * sig;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
