#ifndef SPATIALDOMAINDEFINITION_HPP
#define SPATIALDOMAINDEFINITION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SpatialDomainDefinition {

constexpr int EQUATION_NUMBER = 13;
constexpr const char* TITLE = "Spatial Domain Definition";
constexpr const char* LATEX = R"(\Omega = \left\{(i,j) \mid 0 \le i < W,\; 0 \le j < H \right\})";
constexpr const char* MEANING = "Defines the 2D pixel grid domain";
constexpr const char* CODE_ROLE = "Defines screen resolution constants";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {14, 15};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 2;

inline bool validate_pixel_coords(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
