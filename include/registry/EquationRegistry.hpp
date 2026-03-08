#ifndef EQUATION_REGISTRY_HPP
#define EQUATION_REGISTRY_HPP

#include "../common/StableArchetypeCommon.hpp"

namespace EquationRegistry {

struct EquationInfo {
    int number;
    const char* title;
    const char* latex;
    const char* subsystem;
    const char* runtime_placement;
    const int* upstream_deps;
    const int* downstream_deps;
    int num_upstream;
    int num_downstream;
};

// Forward declarations for all equation accessors
namespace Equation001 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation002 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation003 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation004 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation005 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation006 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation007 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation008 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation009 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation010 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation011 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }
namespace Equation012 { const char* get_latex(); const char* get_title(); const char* get_subsystem(); }

// Subsystem enumeration
enum Subsystem {
    SUBSYSTEM_ARCHETYPE_ONTOLOGY = 0,
    SUBSYSTEM_SPATIAL_GEOMETRY,
    SUBSYSTEM_CONTEXT_EVOLUTION,
    SUBSYSTEM_PIXEL_INPUT_SYNTHESIS,
    SUBSYSTEM_ARCHETYPE_NEURAL_EVALUATION,
    SUBSYSTEM_CONTROLLER_GATING,
    SUBSYSTEM_BLENDING,
    SUBSYSTEM_SEMANTIC_DIAGNOSTICS,
    SUBSYSTEM_TEMPORAL_DIAGNOSTICS,
    SUBSYSTEM_FINAL_COLOR_SYNTHESIS,
    SUBSYSTEM_COUNT
};

// Get subsystem name from enum
inline const char* get_subsystem_name(Subsystem s) {
    static const char* names[] = {
        "archetype_ontology",
        "spatial_geometry",
        "context_evolution",
        "pixel_input_synthesis",
        "archetype_neural_evaluation",
        "controller_gating",
        "blending",
        "semantic_diagnostics",
        "temporal_diagnostics",
        "final_color_synthesis"
    };
    return (s >= 0 && s < SUBSYSTEM_COUNT) ? names[s] : "unknown";
}

// Get equation subsystem
inline Subsystem get_equation_subsystem(int eq_num) {
    if (eq_num >= 1 && eq_num <= 12) return SUBSYSTEM_ARCHETYPE_ONTOLOGY;
    if (eq_num >= 13 && eq_num <= 20) return SUBSYSTEM_SPATIAL_GEOMETRY;
    if (eq_num >= 21 && eq_num <= 30) return SUBSYSTEM_CONTEXT_EVOLUTION;
    if (eq_num >= 31 && eq_num <= 40) return SUBSYSTEM_PIXEL_INPUT_SYNTHESIS;
    if (eq_num >= 41 && eq_num <= 50) return SUBSYSTEM_ARCHETYPE_NEURAL_EVALUATION;
    if (eq_num >= 51 && eq_num <= 60) return SUBSYSTEM_CONTROLLER_GATING;
    if (eq_num >= 61 && eq_num <= 70) return SUBSYSTEM_BLENDING;
    if (eq_num >= 71 && eq_num <= 80) return SUBSYSTEM_SEMANTIC_DIAGNOSTICS;
    if (eq_num >= 81 && eq_num <= 90) return SUBSYSTEM_TEMPORAL_DIAGNOSTICS;
    if (eq_num >= 91 && eq_num <= 100) return SUBSYSTEM_FINAL_COLOR_SYNTHESIS;
    return SUBSYSTEM_COUNT;
}

// Get equation info
inline EquationInfo get_equation_info(int eq_num) {
    EquationInfo info = {0, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0};
    
    switch(eq_num) {
        case 1: info = {1, "Archetype Library Definition", Equation001::get_latex(), Equation001::get_subsystem(), "CPU/LibTorch", nullptr, nullptr, 0, 7}; break;
        case 2: info = {2, "Archetype Count", Equation002::get_latex(), Equation002::get_subsystem(), "CPU", nullptr, nullptr, 1, 12}; break;
        case 3: info = {3, "Archetype Parameter Structure", Equation003::get_latex(), Equation003::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 2, 4}; break;
        case 4: info = {4, "Parameter Stability", Equation004::get_latex(), Equation004::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 1, 2}; break;
        case 5: info = {5, "Archetype Semantic Types", Equation005::get_latex(), Equation005::get_subsystem(), "CPU", nullptr, nullptr, 2, 5}; break;
        case 6: info = {6, "Parameter Source Modes", Equation006::get_latex(), Equation006::get_subsystem(), "CPU/LibTorch", nullptr, nullptr, 1, 1}; break;
        case 7: info = {7, "Unified Parameter Set", Equation007::get_latex(), Equation007::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 2, 3}; break;
        case 8: info = {8, "Archetype Function Signature", Equation008::get_latex(), Equation008::get_subsystem(), "OpenCL", nullptr, nullptr, 4, 2}; break;
        case 9: info = {9, "Spatial Input Dimension", Equation009::get_latex(), Equation009::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 0, 4}; break;
        case 10: info = {10, "Context Input Dimension", Equation010::get_latex(), Equation010::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 0, 5}; break;
        case 11: info = {11, "Output Color Dimension", Equation011::get_latex(), Equation011::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 0, 5}; break;
        case 12: info = {12, "Hidden Layer Width", Equation012::get_latex(), Equation012::get_subsystem(), "CPU/OpenCL", nullptr, nullptr, 0, 3}; break;
    }
    
    return info;
}

// Validate equation number
inline bool is_valid_equation(int eq_num) {
    return eq_num >= 1 && eq_num <= 100;
}

// Get total equation count
inline int get_total_equations() {
    return 100;
}

}

#endif
