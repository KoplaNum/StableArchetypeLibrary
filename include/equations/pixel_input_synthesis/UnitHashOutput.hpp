#ifndef UNITHASHOUTPUT_HPP
#define UNITHASHOUTPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace UnitHashOutput {

constexpr int EQUATION_NUMBER = 37;
constexpr const char* TITLE = "Unit Hash Output";
constexpr const char* LATEX = R"(\chi_{p,t} = \frac{m_{p,t} \bmod 2^{24}}{2^{24}-1})";
constexpr const char* MEANING = "Normalizes 24-bit hash to [0,1]";
constexpr const char* CODE_ROLE = "Converts mixed hash to unit interval";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {38};
constexpr int DOWNSTREAM_DEPS[] = {36};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline float hash_to_unit(unsigned int m) {
    return (float)(m & 0x00FFFFFFu) / 16777215.0f;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
