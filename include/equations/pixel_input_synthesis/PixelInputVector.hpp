#ifndef PIXELINPUTVECTOR_HPP
#define PIXELINPUTVECTOR_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace PixelInputVector {

constexpr int EQUATION_NUMBER = 31;
constexpr const char* TITLE = "Pixel Input Vector";
constexpr const char* LATEX = R"(\mathbf{z}_{p,t} = \begin{bmatrix} x_p \\ y_p \\ \tilde{c}_{p,t}^{(r)} \\ \tilde{c}_{p,t}^{(v)} \\ \tilde{c}_{p,t}^{(\tau)} \\ \tilde{c}_{p,t}^{(\rho)} \end{bmatrix})";
constexpr const char* MEANING = "6D input: spatial + modulated context per pixel";
constexpr const char* CODE_ROLE = "Constructs full input vector for archetype NN";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {14, 15, 32, 33, 34, 35};
constexpr int DOWNSTREAM_DEPS[] = {39, 40, 41};

constexpr int NUM_UPSTREAM = 6;
constexpr int NUM_DOWNSTREAM = 3;

struct PixelInput {
    float x, y;
    float ctx_r, ctx_v, ctx_t, ctx_rho;
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
