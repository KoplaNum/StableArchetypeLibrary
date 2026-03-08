#ifndef POLARANGLE_HPP
#define POLARANGLE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace PolarAngle {

constexpr int EQUATION_NUMBER = 18;
constexpr const char* TITLE = "Polar Angle";
constexpr const char* LATEX = R"(\vartheta_p = \operatorname{atan2}(y_p,x_p))";
constexpr const char* MEANING = "Angular position in polar coordinates";
constexpr const char* CODE_ROLE = "Computes polar angle (available for patterns)";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15};
constexpr int DOWNSTREAM_DEPS[] = {20};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline float compute_angle(float x, float y) {
    return atan2f(y, x);
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
