#ifndef PBOTEXTUREUPLOAD_HPP
#define PBOTEXTUREUPLOAD_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace PBOTextureUpload {

constexpr int EQUATION_NUMBER = 97;
constexpr const char* TITLE = "PBO Texture Upload";
constexpr const char* LATEX = R"(\mathbf{I}_{p,t}^{\text{PBO}} \xrightarrow{\text{CL/GL share}} \text{texture upload})";
constexpr const char* MEANING = "Zero-copy transfer from OpenCL to OpenGL via PBO";
constexpr const char* CODE_ROLE = "Documents CL/GL interop texture path";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL/OpenGL";

constexpr int UPSTREAM_DEPS[] = {96};
constexpr int DOWNSTREAM_DEPS[] = {98};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
