#ifndef OUTPUT_COLOR_DIMENSION_HPP
#define OUTPUT_COLOR_DIMENSION_HPP

#include "../../common/StableArchetypeCommon.hpp"
namespace OutputColorDimension {

constexpr int EQUATION_NUMBER = 11;
constexpr const char* TITLE = "Output Color Dimension";
constexpr const char* LATEX = R"(d_o = 3)";
constexpr const char* MEANING = "Output is 3D (R, G, B color channels)";
constexpr const char* CODE_ROLE = "Defines output dimension constant";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {8, 44, 45, 63, 95};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 5;


inline int get_output_dim() { return D_O; }
inline bool validate_color_output(float* rgb) {
    if(!rgb) return false;
    for(int i=0; i<D_O; i++) {
        if(rgb[i] < 0.0f || rgb[i] > 1.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
