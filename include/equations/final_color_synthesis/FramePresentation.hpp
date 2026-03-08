#ifndef FRAMEPRESENTATION_HPP
#define FRAMEPRESENTATION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace FramePresentation {

constexpr int EQUATION_NUMBER = 99;
constexpr const char* TITLE = "Frame Presentation";
constexpr const char* LATEX = R"(\text{frame}_{t+1} = \mathcal{Q}\!\left(\text{texture}_{t+1}\right))";
constexpr const char* MEANING = "Renders textured quad to screen";
constexpr const char* CODE_ROLE = "Documents final display operation";
constexpr const char* SUBSYSTEM = "final_color_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenGL";

constexpr int UPSTREAM_DEPS[] = {98};
constexpr int DOWNSTREAM_DEPS[] = {100};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
