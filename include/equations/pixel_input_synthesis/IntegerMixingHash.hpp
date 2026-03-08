// IntegerMixingHash.hpp
// Hash function for per-pixel random integer generation
// Scientific naming based on stable_archetype_100_equations_scientific_handbook.md

#ifndef INTEGER_MIXING_HASH_HPP
#define INTEGER_MIXING_HASH_HPP

#include "../../common/StableArchetypeCommon.hpp"

namespace IntegerMixingHash {

// ============================================================
// Equation Metadata
// ============================================================
constexpr int EQUATION_NUMBER = 38;
constexpr const char* TITLE = "Integer Mixing Hash";
constexpr const char* LATEX = R"(m_{p,t} = h(i,j,u_t))";
constexpr const char* MEANING = "Hash function mixes pixel coords and seed";
constexpr const char* CODE_ROLE = "Generates per-pixel random integer";
constexpr const char* SUBSYSTEM = "pixel_input_synthesis";
constexpr const char* RUNTIME_PLACEMENT = "OpenCL";

// ============================================================
// Hash Mixing Constants (Avalanche Effect Constants)
// These prime numbers ensure good bit distribution in hash output
// ============================================================

// Pixel coordinate mixing multipliers
constexpr unsigned int PIXEL_COLUMN_MULTIPLIER = 1973u;    // Prime for i coordinate
constexpr unsigned int PIXEL_ROW_MULTIPLIER = 9277u;       // Prime for j coordinate

// Seed mixing constants
constexpr unsigned int SEED_MULTIPLIER = 26699u;           // Prime for temporal seed
constexpr unsigned int SEED_OFFSET = 911u;                 // Prime offset

// Avalanche effect constants (ensure small input changes cause large output changes)
constexpr unsigned int AVALANCHE_SHIFT = 13u;              // Bit shift for mixing
constexpr unsigned int AVALANCHE_MULTIPLIER_1 = 15731u;    // Prime multiplier (first stage)
constexpr unsigned int AVALANCHE_OFFSET = 789221u;         // Prime offset
constexpr unsigned int AVALANCHE_MULTIPLIER_2 = 3266489917u; // Large prime (second stage)
constexpr unsigned int AVALANCHE_FINAL_OFFSET = 1376312589u; // Final prime offset

// Bit mask for extracting lower 24 bits
constexpr unsigned int HASH_OUTPUT_MASK = 0x00FFFFFFu;     // 24-bit mask
constexpr float HASH_OUTPUT_NORMALIZER = 1.0f / 16777215.0f;  // 1/(2^24-1)

// ============================================================
// Hash Mixing Function
// ============================================================
inline unsigned int mix_pixel_hash(unsigned int pixelColumn, unsigned int pixelRow, unsigned int temporalSeed) {
    // Initial mixing of spatial and temporal components
    unsigned int mixedHash = (pixelColumn * PIXEL_COLUMN_MULTIPLIER) 
                           ^ (pixelRow * PIXEL_ROW_MULTIPLIER) 
                           ^ (temporalSeed * SEED_MULTIPLIER + SEED_OFFSET);
    
    // First avalanche stage: XOR shift
    mixedHash = (mixedHash << AVALANCHE_SHIFT) ^ mixedHash;
    
    // Second avalanche stage: multiplication and addition
    mixedHash = mixedHash * (mixedHash * AVALANCHE_MULTIPLIER_1 + AVALANCHE_OFFSET) + AVALANCHE_FINAL_OFFSET;
    
    return mixedHash;
}

// ============================================================
// Normalization Function (for unit interval output)
// ============================================================
inline float normalize_hash_to_unit(unsigned int mixedHash) {
    return static_cast<float>(mixedHash & HASH_OUTPUT_MASK) * HASH_OUTPUT_NORMALIZER;
}

// ============================================================
// Accessor Functions
// ============================================================
inline const char* get_latex() { return LATEX; }
inline const char* get_title() { return TITLE; }
inline const char* get_subsystem() { return SUBSYSTEM; }

}  // namespace IntegerMixingHash

#endif
