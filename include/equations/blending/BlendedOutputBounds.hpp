#ifndef BLENDEDOUTPUTBOUNDS_HPP
#define BLENDEDOUTPUTBOUNDS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace BlendedOutputBounds {

constexpr int EQUATION_NUMBER = 63;
constexpr const char* TITLE = "Blended Output Bounds";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t} \in [0,1]^3)";
constexpr const char* MEANING = "Blended output remains in valid color range";
constexpr const char* CODE_ROLE = "Validates blended output range";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {11, 54, 55, 61};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 0;

inline bool validate_blended(float* o) {
    if(!o) return false;
    for(int c=0; c<3; c++) {
        if(o[c] < 0.0f || o[c] > 1.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
