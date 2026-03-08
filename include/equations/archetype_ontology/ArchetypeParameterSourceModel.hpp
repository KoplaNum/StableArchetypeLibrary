#ifndef ARCHETYPE_PARAMETER_SOURCE_MODEL_HPP
#define ARCHETYPE_PARAMETER_SOURCE_MODEL_HPP

namespace ArchetypeParameterSourceModel {

constexpr int EQUATION_NUMBER = 6;
constexpr const char* TITLE = "Parameter Source Modes";
constexpr const char* LATEX = R"(\Theta_k = \begin{cases} \Theta_k^{\text{fixed-seed}}, & \text{deterministic} \\ \Theta_k^{\text{TorchScript}}, & \text{offline-trained} \end{cases})";
constexpr const char* MEANING = "Parameters come from fixed seed or TorchScript export";
constexpr const char* CODE_ROLE = "Selects parameter initialization mode";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/LibTorch";

constexpr int UPSTREAM_DEPS[] = {3};
constexpr int DOWNSTREAM_DEPS[] = {7};

constexpr int NUM_UPSTREAM = 1;
constexpr int NUM_DOWNSTREAM = 1;

enum ParamSource {
    PARAM_FIXED_SEED = 0,
    PARAM_TORCHSCRIPT = 1
};

inline ParamSource get_param_source(bool use_torchscript) {
    return use_torchscript ? PARAM_TORCHSCRIPT : PARAM_FIXED_SEED;
}

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
