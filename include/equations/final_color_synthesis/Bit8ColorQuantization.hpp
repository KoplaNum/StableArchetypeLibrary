#ifndef BIT8COLORQUANTIZATION_HPP
#define BIT8COLORQUANTIZATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace Bit8ColorQuantization {

constexpr int EQUATION_NUMBER = 96;
constexpr const char* TITLE = "8-bit Color Quantization";
constexpr const char* LATEX = R"(\mathbf{I}_{p,t}^{(8)} = 255 \cdot \mathbf{I}_{p,t})";
constexpr const char* MEANING = "Scales [0,1] float colors to [0,255] byte range";
constexpr const char* CODE_ROLE = "Converts float colors to 8-bit for display";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {95};
constexpr int DOWNSTREAM_DEPS[] = {97};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline unsigned char float_to_byte(float c) {
    int v = (int)(c * 255.0f + 0.5f);
    return (unsigned char)((v < 0) ? 0 : ((v > 255) ? 255 : v));
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
