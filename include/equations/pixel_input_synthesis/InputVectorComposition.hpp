#ifndef INPUTVECTORCOMPOSITION_HPP
#define INPUTVECTORCOMPOSITION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace InputVectorComposition {

constexpr int EQUATION_NUMBER = 40;
constexpr const char* TITLE = "Input Vector Composition";
constexpr const char* LATEX = R"(\mathbf{z}_{p,t} = \mathbf{s}_p \oplus \tilde{\mathbf{c}}_{p,t})";
constexpr const char* MEANING = "Concatenation of spatial and context vectors";
constexpr const char* CODE_ROLE = "Describes input structure";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {16, 31};
constexpr int DOWNSTREAM_DEPS[] = {41};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
