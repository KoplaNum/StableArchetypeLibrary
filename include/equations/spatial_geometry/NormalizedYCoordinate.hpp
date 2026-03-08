#ifndef NORMALIZEDYCOORDINATE_HPP
#define NORMALIZEDYCOORDINATE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace NormalizedYCoordinate {

constexpr int EQUATION_NUMBER = 15;
constexpr const char* TITLE = "Normalized Y Coordinate";
constexpr const char* LATEX = R"(y_p = \frac{2j}{H-1} - 1)";
constexpr const char* MEANING = "Maps pixel row to [-1, 1] range";
constexpr const char* CODE_ROLE = "Computes normalized y coordinate per pixel";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {13};
constexpr int DOWNSTREAM_DEPS[] = {16, 17, 18, 20, 31};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 6;

inline float normalize_y(int j, int height) {
    return (height > 1) ? (2.0f * (float)j / (float)(height - 1)) - 1.0f : 0.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
