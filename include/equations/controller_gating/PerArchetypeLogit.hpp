#ifndef PERARCHETYPELOGIT_HPP
#define PERARCHETYPELOGIT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace PerArchetypeLogit {

constexpr int EQUATION_NUMBER = 52;
constexpr const char* TITLE = "Per-Archetype Logit";
constexpr const char* LATEX = R"(q_{k,t} = u_k^\top \mathbf{c}_t + b_{q,k})";
constexpr const char* MEANING = "Scalar logit for archetype k from context";
constexpr const char* CODE_ROLE = "Computes single archetype score";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {21, 51};
constexpr int DOWNSTREAM_DEPS[] = {53};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline float compute_logit(float* u_k, float* c, float bq_k, int d_c) {
    float q = bq_k;
    for(int i=0; i<d_c; i++) {
        q += u_k[i] * c[i];
    }
    return q;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
