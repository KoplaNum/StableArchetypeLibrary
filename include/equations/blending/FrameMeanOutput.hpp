#ifndef FRAMEMEANOUTPUT_HPP
#define FRAMEMEANOUTPUT_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace FrameMeanOutput {

constexpr int EQUATION_NUMBER = 69;
constexpr const char* TITLE = "Frame Mean Output";
constexpr const char* LATEX = R"(\bar{\mathbf{o}}_t = \frac{1}{|\Omega|}\sum_{p\in\Omega}\mathbf{o}_{p,t})";
constexpr const char* MEANING = "Average blended color across all pixels";
constexpr const char* CODE_ROLE = "Computes frame-level color statistics";
constexpr const char* SUBSYSTEM = "blending";
constexpr const char* RUNTIME_PLACEMENT = "CPU";

constexpr int UPSTREAM_DEPS[] = {13, 61};
constexpr int DOWNSTREAM_DEPS[] = {70};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 1;

inline void compute_mean_output(float* mean, float* frame_buffer, int W, int H) {
    int N = W * H;
    mean[0] = mean[1] = mean[2] = 0.0f;
    for(int p=0; p<N; p++) {
        mean[0] += frame_buffer[p * 3 + 0];
        mean[1] += frame_buffer[p * 3 + 1];
        mean[2] += frame_buffer[p * 3 + 2];
    }
    float invN = 1.0f / (float)N;
    mean[0] *= invN;
    mean[1] *= invN;
    mean[2] *= invN;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
