#ifndef OUTPUTTEMPORALUPDATE_HPP
#define OUTPUTTEMPORALUPDATE_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace OutputTemporalUpdate {

constexpr int EQUATION_NUMBER = 83;
constexpr const char* TITLE = "Output Temporal Update";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t+1} = \sum_{k=1}^{K}\pi_k(t+1)\Phi_k(\mathbf{z}_{p,t+1}))";
constexpr const char* MEANING = "Next frame output from updated gating and inputs";
constexpr const char* CODE_ROLE = "Defines frame-to-frame output evolution";
constexpr const char* SUBSYSTEM = "temporal_diagnostics";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {48, 53, 61, 82};
constexpr int DOWNSTREAM_DEPS[] = {84};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
