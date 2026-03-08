#ifndef INPUTBOUNDSVALIDATION_HPP
#define INPUTBOUNDSVALIDATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace InputBoundsValidation {

constexpr int EQUATION_NUMBER = 39;
constexpr const char* TITLE = "Input Bounds";
constexpr const char* LATEX = R"(\mathbf{z}_{p,t} \in [-1,1]^6)";
constexpr const char* MEANING = "All input components bounded to [-1,1]";
constexpr const char* CODE_ROLE = "Validates input range";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {31};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 0;

inline bool validate_input(float* z) {
    if(!z) return false;
    for(int i=0; i<6; i++) {
        if(z[i] < -1.0f || z[i] > 1.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
