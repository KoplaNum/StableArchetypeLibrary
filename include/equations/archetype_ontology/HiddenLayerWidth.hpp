#ifndef HIDDEN_LAYER_WIDTH_HPP
#define HIDDEN_LAYER_WIDTH_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace HiddenLayerWidth {

constexpr int EQUATION_NUMBER = 12;
constexpr const char* TITLE = "Hidden Layer Width";
constexpr const char* LATEX = R"(d_h = 16)";
constexpr const char* MEANING = "Each archetype MLP has 16 hidden units";
constexpr const char* CODE_ROLE = "Defines hidden layer dimension constant";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {41, 42, 43};

constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 3;

inline int get_hidden_dim() { return D_H; }
inline size_t get_layer1_size() { return (size_t)NN_H * (size_t)NN_IN; }
inline size_t get_layer2_size() { return (size_t)NN_OUT * (size_t)NN_H; }

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
