#ifndef STABLE_ARCHETYPE_LIBRARY_HPP
#define STABLE_ARCHETYPE_LIBRARY_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace StableArchetypeLibrary {

constexpr int EQUATION_NUMBER = 1;
constexpr const char* TITLE = "Archetype Library Definition";
constexpr const char* LATEX = R"(\mathfrak{A} = \left\{ \mathcal{A}_1,\mathcal{A}_2,\ldots,\mathcal{A}_K \right\})";
constexpr const char* MEANING = "Defines the archetype library as a set of K distinct neural operators";
constexpr const char* CODE_ROLE = "Declares the archetype library container structure";
constexpr const char* SUBSYSTEM = "archetype_ontology";
constexpr const char* RUNTIME_PLACEMENT = "CPU/LibTorch";

const int* UPSTREAM_DEPS = nullptr;
constexpr int DOWNSTREAM_DEPS[] = {2, 3, 4, 5, 6, 7, 8};
constexpr int NUM_UPSTREAM = 0;
constexpr int NUM_DOWNSTREAM = 7;

struct ArchetypeLibrary {
    int K;
    void** archetypes;
    
    inline bool validate() const {
        return K == K_ARCHETYPES && K > 0 && archetypes != nullptr;
    }
};

inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}

#endif
