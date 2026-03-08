#ifndef ARCHETYPE_FUNCTION_SIGNATURE_HPP
#define ARCHETYPE_FUNCTION_SIGNATURE_HPP

namespace ArchetypeFunctionSignature {

constexpr int EQUATION_NUMBER = 8;
constexpr const char* TITLE = "Archetype Function Signature";
constexpr const char* LATEX = R"(\mathcal{A}_k : \mathbb{R}^{d_s+d_c} \to \mathbb{R}^{d_o})";
constexpr const char* MEANING = "Each archetype maps spatial+context input to color output";
constexpr const char* CODE_ROLE = "Defines archetype evaluation function type";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

constexpr int UPSTREAM_DEPS[] = {1, 9, 10, 11};
constexpr int DOWNSTREAM_DEPS[] = {47, 48};

constexpr int NUM_UPSTREAM = 4;
constexpr int NUM_DOWNSTREAM = 2;

using ArchetypeFunc = void(*)(float x, float y, float* ctx, float* out_rgb);

inline void validate_io_dims(int in_dim, int out_dim) {
    (void)in_dim; (void)out_dim;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
