#ifndef DOMINANTARCHETYPESELECTION_HPP
#define DOMINANTARCHETYPESELECTION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace DominantArchetypeSelection {

constexpr int EQUATION_NUMBER = 57;
constexpr const char* TITLE = "Dominant Archetype Selection";
constexpr const char* LATEX = R"(k_t^\star = \arg\max_{k}\pi_k(t))";
constexpr const char* MEANING = "Index of highest-weighted archetype";
constexpr const char* CODE_ROLE = "Finds winning archetype for hard selection";
constexpr const char* SUBSYSTEM = "controller_gating";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {2, 53};
constexpr int DOWNSTREAM_DEPS[] = {64};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline int argmax(float* pi, int K) {
    int best = 0;
    float max_w = pi[0];
    for(int k=1; k<K; k++) {
        if(pi[k] > max_w) {
            max_w = pi[k];
            best = k;
        }
    }
    return best;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
