#ifndef FINALCOLORVECTOR_HPP
#define FINALCOLORVECTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace FinalColorVector {

constexpr int EQUATION_NUMBER = 95;
constexpr const char* TITLE = "Final Color Vector";
constexpr const char* LATEX = R"(\mathbf{I}_{p,t} = \begin{bmatrix} R_{p,t} \\ G_{p,t} \\ B_{p,t} \end{bmatrix})";
constexpr const char* MEANING = "Complete RGB color triplet for display";
constexpr const char* CODE_ROLE = "Packages final color channels";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {11, 92, 93, 94};
constexpr int DOWNSTREAM_DEPS[] = {96, 97, 100};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 3;

struct FinalColor {
    float R, G, B;
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
