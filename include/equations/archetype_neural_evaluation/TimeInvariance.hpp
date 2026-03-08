#ifndef TIMEINVARIANCE_HPP
#define TIMEINVARIANCE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace TimeInvariance {

constexpr int EQUATION_NUMBER = 50;
constexpr const char* TITLE = "Time Invariance";
constexpr const char* LATEX = R"(\Phi_k \text{ is time-invariant whenever } \Theta_k \text{ is fixed})";
constexpr const char* MEANING = "Fixed weights produce stable visual identity";
constexpr const char* CODE_ROLE = "Enforces archetype stability across frames";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {4, 48};
constexpr int DOWNSTREAM_DEPS[] = {90};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline bool verify_time_invariance(float* out1, float* out2, int size, float tol=1e-5f) {
    if(!out1 || !out2) return false;
    for(int i=0; i<size; i++) {
        float d = out1[i] - out2[i];
        if(d < -tol || d > tol) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
