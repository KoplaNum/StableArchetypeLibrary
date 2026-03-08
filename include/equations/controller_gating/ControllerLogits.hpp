#ifndef CONTROLLERLOGITS_HPP
#define CONTROLLERLOGITS_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace ControllerLogits {

constexpr int EQUATION_NUMBER = 51;
constexpr const char* TITLE = "Controller Logits";
constexpr const char* LATEX = R"(\mathbf{q}_t = U \mathbf{c}_t + b_q)";
constexpr const char* MEANING = "Linear map from context to archetype logits";
constexpr const char* CODE_ROLE = "Computes raw archetype scores from context";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 10, 21};
constexpr int DOWNSTREAM_DEPS[] = {52, 53};

constexpr int NUM_UPSTREAM = 3;
constexpr int NUM_DOWNSTREAM = 2;

inline void compute_logits(float* q, float* U, float* bq, float* c, int K, int d_c) {
    for(int k=0; k<K; k++) {
        q[k] = bq[k];
        for(int i=0; i<d_c; i++) {
            q[k] += U[k * d_c + i] * c[i];
        }
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
