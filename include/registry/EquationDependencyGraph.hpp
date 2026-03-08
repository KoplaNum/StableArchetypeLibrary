#ifndef EQUATION_DEPENDENCY_GRAPH_HPP
#define EQUATION_DEPENDENCY_GRAPH_HPP

#include "../common/StableArchetypeCommon.hpp"

namespace EquationDependencyGraph {

constexpr int MAX_EQUATIONS = 100;
constexpr int MAX_DEPS_PER_EQUATION = 10;

// Dependency graph structure
struct DependencyGraph {
    int num_equations;
    int upstream[MAX_EQUATIONS][MAX_DEPS_PER_EQUATION];
    int downstream[MAX_EQUATIONS][MAX_DEPS_PER_EQUATION];
    int num_upstream[MAX_EQUATIONS];
    int num_downstream[MAX_EQUATIONS];
};

// Initialize dependency graph with known dependencies
inline void init_dependency_graph(DependencyGraph& graph) {
    graph.num_equations = 100;
    
    // Initialize all to zero
    for(int i = 0; i < MAX_EQUATIONS; i++) {
        graph.num_upstream[i] = 0;
        graph.num_downstream[i] = 0;
        for(int j = 0; j < MAX_DEPS_PER_EQUATION; j++) {
            graph.upstream[i][j] = 0;
            graph.downstream[i][j] = 0;
        }
    }
    
    // Equation 1: Archetype Library Definition (no upstream, downstream: 2,3,4,5,6,7,8)
    graph.num_downstream[0] = 7;
    graph.downstream[0][0] = 2; graph.downstream[0][1] = 3; graph.downstream[0][2] = 4;
    graph.downstream[0][3] = 5; graph.downstream[0][4] = 6; graph.downstream[0][5] = 7;
    graph.downstream[0][6] = 8;
    
    // Equation 2: Archetype Count (upstream: 1, downstream: 3,53,54,55,57,58,59,61,62,64,65,66)
    graph.num_upstream[1] = 1;
    graph.upstream[1][0] = 1;
    graph.num_downstream[1] = 12;
    graph.downstream[1][0] = 3; graph.downstream[1][1] = 53; graph.downstream[1][2] = 54;
    graph.downstream[1][3] = 55; graph.downstream[1][4] = 57; graph.downstream[1][5] = 58;
    graph.downstream[1][6] = 59; graph.downstream[1][7] = 61; graph.downstream[1][8] = 62;
    graph.downstream[1][9] = 64; graph.downstream[1][10] = 65; graph.downstream[1][11] = 66;
    
    // Equation 3: Archetype Parameter Structure (upstream: 1,2, downstream: 4,7,41,43)
    graph.num_upstream[2] = 2;
    graph.upstream[2][0] = 1; graph.upstream[2][1] = 2;
    graph.num_downstream[2] = 4;
    graph.downstream[2][0] = 4; graph.downstream[2][1] = 7;
    graph.downstream[2][2] = 41; graph.downstream[2][3] = 43;
    
    // Equation 100: Complete Renderer Summary (upstream: 21,53,61,95)
    graph.num_upstream[99] = 4;
    graph.upstream[99][0] = 21; graph.upstream[99][1] = 53;
    graph.upstream[99][2] = 61; graph.upstream[99][3] = 95;
}

// Check if equation A depends on equation B (direct dependency)
inline bool has_direct_dependency(int eq_a, int eq_b) {
    if(eq_a < 1 || eq_a > 100 || eq_b < 1 || eq_b > 100) return false;
    
    DependencyGraph graph;
    init_dependency_graph(graph);
    
    int idx = eq_a - 1;
    for(int i = 0; i < graph.num_upstream[idx]; i++) {
        if(graph.upstream[idx][i] == eq_b) return true;
    }
    return false;
}

// Get dependency path length (simplified)
inline int get_dependency_depth(int eq_num) {
    if(eq_num < 1 || eq_num > 100) return -1;
    
    // Approximate depth based on equation number ranges
    if(eq_num <= 12) return 1;       // Archetype Ontology
    if(eq_num <= 20) return 2;       // Spatial Geometry
    if(eq_num <= 30) return 3;       // Context Evolution
    if(eq_num <= 40) return 4;       // Pixel Input Synthesis
    if(eq_num <= 50) return 5;       // Archetype Neural Evaluation
    if(eq_num <= 60) return 6;       // Controller/Gating
    if(eq_num <= 70) return 7;       // Blending
    if(eq_num <= 80) return 8;       // Semantic Diagnostics
    if(eq_num <= 90) return 9;       // Temporal Diagnostics
    return 10;                        // Final Color Synthesis
}

// Get equations by subsystem
inline int get_equations_by_subsystem(int subsystem_id, int* out_equations, int max_out) {
    int count = 0;
    int start = 0, end = 0;
    
    switch(subsystem_id) {
        case 0: start = 1; end = 12; break;   // Archetype Ontology
        case 1: start = 13; end = 20; break;  // Spatial Geometry
        case 2: start = 21; end = 30; break;  // Context Evolution
        case 3: start = 31; end = 40; break;  // Pixel Input Synthesis
        case 4: start = 41; end = 50; break;  // Archetype Neural Evaluation
        case 5: start = 51; end = 60; break;  // Controller/Gating
        case 6: start = 61; end = 70; break;  // Blending
        case 7: start = 71; end = 80; break;  // Semantic Diagnostics
        case 8: start = 81; end = 90; break;  // Temporal Diagnostics
        case 9: start = 91; end = 100; break; // Final Color Synthesis
        default: return 0;
    }
    
    for(int i = start; i <= end && count < max_out; i++) {
        out_equations[count++] = i;
    }
    
    return count;
}

}

#endif
