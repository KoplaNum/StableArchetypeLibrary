#ifndef CONTEXT_INPUT_DIMENSION_HPP
#define CONTEXT_INPUT_DIMENSION_HPP

#include "../../common/StableArchetypeCommon.hpp"
namespace ContextInputDimension {

constexpr int EQUATION_NUMBER = 10;
constexpr const char* TITLE = "Context Input Dimension";
constexpr const char* LATEX = R"(d_c = 4)";
constexpr const char* MEANING = "Context input is 4D (regime, volatility, trend, risk)";
constexpr const char* CODE_ROLE = "Defines context dimension constant";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {8, 21, 31, 39, 51};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 5;


inline int get_context_dim() { return D_C; }
inline bool validate_context_input(float* ctx) {
    if(!ctx) return false;
    for(int i=0; i<D_C; i++) {
        if(ctx[i] < -1.0f || ctx[i] > 1.0f) return false;
    }
    return true;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
