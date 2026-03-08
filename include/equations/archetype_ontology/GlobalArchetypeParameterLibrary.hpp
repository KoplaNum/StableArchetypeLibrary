#ifndef GLOBAL_ARCHETYPE_PARAMETER_LIBRARY_HPP
#define GLOBAL_ARCHETYPE_PARAMETER_LIBRARY_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace GlobalArchetypeParameterLibrary {

constexpr int EQUATION_NUMBER = 7;
constexpr const char* TITLE = "Unified Parameter Set";
constexpr const char* LATEX = R"(\Theta = \bigcup_{k=1}^{K}\Theta_k)";
constexpr const char* MEANING = "All archetype parameters form the unified library";
constexpr const char* CODE_ROLE = "Aggregates all archetype weights into buffer";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/OpenCL";

constexpr int UPSTREAM_DEPS[] = {3, 6};
constexpr int DOWNSTREAM_DEPS[] = {41, 43, 61};

constexpr int NUM_UPSTREAM = 2;
constexpr int NUM_DOWNSTREAM = 3;

struct UnifiedParameterBuffer {
    float** all_W1;
    float** all_b1;
    float** all_W2;
    float** all_b2;
    
    inline bool validate() const {
        for(int k=0; k<K_ARCHETYPES; k++) {
            if(!all_W1[k] || !all_b1[k] || !all_W2[k] || !all_b2[k])
                return false;
        }
        return true;
    }
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
