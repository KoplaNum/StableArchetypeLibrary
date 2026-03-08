#ifndef NORMALIZEDXCOORDINATE_HPP
#define NORMALIZEDXCOORDINATE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace NormalizedXCoordinate {

constexpr int EQUATION_NUMBER = 14;
constexpr const char* TITLE = "Normalized X Coordinate";
constexpr const char* LATEX = R"(x_p = \frac{2i}{W-1} - 1)";
constexpr const char* MEANING = "Maps pixel column to [-1, 1] range";
constexpr const char* CODE_ROLE = "Computes normalized x coordinate per pixel";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {13};
constexpr int DOWNSTREAM_DEPS[] = {16, 17, 18, 20, 31};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 6;

inline float normalize_x(int i, int width) {
    return (width > 1) ? (2.0f * (float)i / (float)(width - 1)) - 1.0f : 0.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
