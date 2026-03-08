#ifndef SIGNEDSTOCHASTICEXCITATION_HPP
#define SIGNEDSTOCHASTICEXCITATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SignedStochasticExcitation {

constexpr int EQUATION_NUMBER = 29;
constexpr const char* TITLE = "Unit Noise Generation";
constexpr const char* LATEX = R"(\eta_t^{(q)} = 2u_t^{(q)} - 1)";
constexpr const char* MEANING = "Maps unit random to [-1, 1] range";
constexpr const char* CODE_ROLE = "Converts unit random to signed noise";
constexpr const char* SUBSYSTEM = "context_evolution";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {30};
constexpr int DOWNSTREAM_DEPS[] = {22, 23, 24, 25};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 4;

inline float unit_to_noise(float u) {
    return 2.0f * u - 1.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
