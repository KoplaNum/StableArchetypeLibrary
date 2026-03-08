#ifndef RADIALDISTANCE_HPP
#define RADIALDISTANCE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace RadialDistance {

constexpr int EQUATION_NUMBER = 17;
constexpr const char* TITLE = "Radial Distance";
constexpr const char* LATEX = R"(r_p = \sqrt{x_p^2 + y_p^2})";
constexpr const char* MEANING = "Distance from center of screen";
constexpr const char* CODE_ROLE = "Computes radial distance for vignette";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15};
constexpr int DOWNSTREAM_DEPS[] = {19, 92, 93};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 3;

inline float compute_radius(float x, float y) {
    return sqrtf(x * x + y * y);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
