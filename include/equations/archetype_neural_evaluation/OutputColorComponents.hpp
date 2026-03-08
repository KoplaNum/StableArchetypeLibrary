#ifndef OUTPUTCOLORCOMPONENTS_HPP
#define OUTPUTCOLORCOMPONENTS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OutputColorComponents {

constexpr int EQUATION_NUMBER = 45;
constexpr const char* TITLE = "Output Color Components";
constexpr const char* LATEX = R"(\mathbf{o}_{k,p,t} = \begin{bmatrix} o_{k,p,t}^{(R)} \\ o_{k,p,t}^{(G)} \\ o_{k,p,t}^{(B)} \end{bmatrix})";
constexpr const char* MEANING = "Archetype output is RGB color triplet";
constexpr const char* CODE_ROLE = "Defines output color structure";
constexpr const char* SUBSYSTEM = "archetype_neural_evaluation";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {11, 44};
constexpr int DOWNSTREAM_DEPS[] = {62};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

struct ArchetypeOutput {
    float R, G, B;
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
