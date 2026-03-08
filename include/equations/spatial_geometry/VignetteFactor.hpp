#ifndef VIGNETTEFACTOR_HPP
#define VIGNETTEFACTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace VignetteFactor {

constexpr int EQUATION_NUMBER = 19;
constexpr const char* TITLE = "Vignette Factor";
constexpr const char* LATEX = R"(v_p = \max(0, 1.15 - r_p))";
constexpr const char* MEANING = "Radial falloff for edge darkening";
constexpr const char* CODE_ROLE = "Computes vignette multiplier";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {17};
constexpr int DOWNSTREAM_DEPS[] = {92, 93};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 2;

inline float compute_vignette(float r) {
    float v = 1.15f - r;
    return (v > 0.0f) ? v : 0.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
