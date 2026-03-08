#ifndef HARDVSSOFTSELECTION_HPP
#define HARDVSSOFTSELECTION_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace HardVsSoftSelection {

constexpr int EQUATION_NUMBER = 64;
constexpr const char* TITLE = "Hard vs Soft Selection";
constexpr const char* LATEX = R"(\mathbf{o}_{p,t} = \begin{cases} \mathbf{o}_{k_t^\star,p,t}, & \text{hard} \\ \sum_{k=1}^{K}\pi_k(t)\mathbf{o}_{k,p,t}, & \text{soft} \end{cases})";
constexpr const char* MEANING = "Output is either dominant archetype or blended";
constexpr const char* CODE_ROLE = "Selects hard or soft blending mode";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {47, 53, 57, 61};
constexpr int DOWNSTREAM_DEPS[] = {65};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 1;

inline void select_output(float* out, float** o_k, float* pi, int k_star, int K, int d_o, bool hard) {
    if(hard) {
        for(int c=0; c<d_o; c++) out[c] = o_k[k_star][c];
    } else {
        for(int c=0; c<d_o; c++) out[c] = 0.0f;
        for(int k=0; k<K; k++) {
            for(int c=0; c<d_o; c++) {
                out[c] += pi[k] * o_k[k][c];
            }
        }
    }
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
