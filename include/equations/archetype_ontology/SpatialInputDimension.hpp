#ifndef SPATIAL_INPUT_DIMENSION_HPP
#define SPATIAL_INPUT_DIMENSION_HPP

#include "../../common/StableArchetypeCommon.hpp"
namespace SpatialInputDimension {

constexpr int EQUATION_NUMBER = 9;
constexpr const char* TITLE = "Spatial Input Dimension";
constexpr const char* LATEX = R"(d_s = 2)";
constexpr const char* MEANING = "Spatial input is 2D (x, y pixel coordinates)";
constexpr const char* CODE_ROLE = "Defines spatial dimension constant";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {8, 31, 39, 41};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 4;


inline int get_spatial_dim() { return D_S; }
inline bool validate_spatial_input(float x, float y) {
    return x >= -1.0f && x <= 1.0f && y >= -1.0f && y <= 1.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
