#ifndef SOFTSELECTIONLIMIT_HPP
#define SOFTSELECTIONLIMIT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace SoftSelectionLimit {

constexpr int EQUATION_NUMBER = 68;
constexpr const char* TITLE = "Soft Selection Limit";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t}^{\text{mix}} \to \mathbf{o}_{p,t} \quad \text{as } \lambda_t \to 1)";
constexpr const char* MEANING = "Unit mixing weight yields pure soft blending";
constexpr const char* CODE_ROLE = "Documents soft selection boundary behavior";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {61, 65};
const int* DOWNSTREAM_DEPS = nullptr;

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 0;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
