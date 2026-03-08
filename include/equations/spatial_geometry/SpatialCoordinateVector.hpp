#ifndef SPATIALCOORDINATEVECTOR_HPP
#define SPATIALCOORDINATEVECTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SpatialCoordinateVector {

constexpr int EQUATION_NUMBER = 16;
constexpr const char* TITLE = "Spatial Coordinate Vector";
constexpr const char* LATEX = R"(\mathbf{s}_p = \begin{bmatrix} x_p \\ y_p \end{bmatrix})";
constexpr const char* MEANING = "2D spatial position as vector";
constexpr const char* CODE_ROLE = "Packages x,y into coordinate vector";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15};
constexpr int DOWNSTREAM_DEPS[] = {40};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

struct SpatialCoord {
    float x, y;
};

inline SpatialCoord make_spatial_coord(float x, float y) {
    SpatialCoord s = {x, y};
    return s;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
