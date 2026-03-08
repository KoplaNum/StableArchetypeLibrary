#ifndef OUTPUTBOUNDSVALIDATION_HPP
#define OUTPUTBOUNDSVALIDATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OutputBoundsValidation {

constexpr int EQUATION_NUMBER = 46;
constexpr const char* TITLE = "Output Bounds";
constexpr const char* LATEX = R"(0 \le o_{k,p,t}^{(c)} \le 1, \qquad c \in \{R,G,B\})";
constexpr const char* MEANING = "Each color channel bounded to unit interval";
constexpr const char* CODE_ROLE = "Validates output color range";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {11, 44};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline bool validate_output(float* rgb) {
    if(!rgb) return false;
    for(int i=0; i<3; i++) {
        if(rgb[i] < 0.0f || rgb[i] > 1.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
