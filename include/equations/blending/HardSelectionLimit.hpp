#ifndef HARDSELECTIONLIMIT_HPP
#define HARDSELECTIONLIMIT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace HardSelectionLimit {

constexpr int EQUATION_NUMBER = 67;
constexpr const char* TITLE = "Hard Selection Limit";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t}^{\text{mix}} \to \mathbf{o}_{k_t^\star,p,t} \quad \text{as } \lambda_t \to 0)";
constexpr const char* MEANING = "Zero mixing weight yields pure hard selection";
constexpr const char* CODE_ROLE = "Documents hard selection boundary behavior";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {65};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
