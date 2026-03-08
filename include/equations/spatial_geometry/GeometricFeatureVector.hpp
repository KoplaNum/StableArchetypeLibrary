#ifndef GEOMETRICFEATUREVECTOR_HPP
#define GEOMETRICFEATUREVECTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace GeometricFeatureVector {

constexpr int EQUATION_NUMBER = 20;
constexpr const char* TITLE = "Geometric Feature Vector";
constexpr const char* LATEX = R"(\mathbf{g}_p = \begin{bmatrix} x_p \\ y_p \\ r_p \\ \vartheta_p \end{bmatrix})";
constexpr const char* MEANING = "Complete geometric description of pixel position";
constexpr const char* CODE_ROLE = "Packages all geometric features";
constexpr const char* SUBSYSTEM = "spatial_geometry";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15, 17, 18};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 0;

struct GeometricFeatures {
    float x, y, r, theta;
};

inline GeometricFeatures make_geo_features(float x, float y, float r, float theta) {
    GeometricFeatures g = {x, y, r, theta};
    return g;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
