#ifndef TEXTUREUPDATE_HPP
#define TEXTUREUPDATE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace TextureUpdate {

constexpr int EQUATION_NUMBER = 98;
constexpr const char* TITLE = "Texture Update";
constexpr const char* LATEX = R"(\text{texture}_{t+1} = \mathcal{U}\!\left(\mathbf{I}_{p,t}^{\text{PBO}}\right))";
constexpr const char* MEANING = "Updates OpenGL texture from PBO for next frame";
constexpr const char* CODE_ROLE = "Documents texture upload operation";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenGL";

constexpr int UPSTREAM_DEPS[] = {97};
constexpr int DOWNSTREAM_DEPS[] = {99};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
