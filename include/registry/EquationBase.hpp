// EquationBase.hpp
// Base class for all 100 equations in Stable Archetype Library
// Enables runtime dependency resolution and graph traversal
//
// Scientific naming conventions based on:
// - stable_archetype_100_equations_scientific_handbook.md
// - stable_archetype_100_equations_deep_handbook.md

#ifndef EQUATION_BASE_HPP
#define EQUATION_BASE_HPP

#include "../common/StableArchetypeCommon.hpp"
#include <vector>
#include <string>
#include <cstring>

namespace EquationSystem {

// Maximum data size for equation I/O
constexpr size_t MAX_DATA_SIZE = 256;

// Equation execution status
enum EquationStatus {
    EQ_NOT_EVALUATED = 0,
    EQ_EVALUATED_OK,
    EQ_EVALUATED_SKIP,
    EQ_EVALUATION_ERROR
};

// Forward declaration
class EquationContext;

// ============================================================
// Base Equation Class (Abstract)
// ============================================================
class Equation {
protected:
    int m_equationNumber;
    const char* m_title;
    const char* m_latex;
    const char* m_meaning;
    const char* m_codeRole;
    const char* m_subsystem;
    const char* m_runtimePlacement;
    
    // Dependency graph connections
    const int* m_upstreamEquationIndices;    // Equations this depends on
    const int* m_downstreamEquationIndices;  // Equations that depend on this
    int m_numUpstreamEquations;
    int m_numDownstreamEquations;
    
    EquationStatus m_status;
    bool m_isEvaluated;

public:
    Equation(int eqNum, const char* title, const char* latex,
             const char* meaning, const char* codeRole,
             const char* subsystem, const char* runtimePlacement,
             const int* upstreamIndices, const int* downstreamIndices,
             int numUpstream, int numDownstream)
        : m_equationNumber(eqNum)
        , m_title(title)
        , m_latex(latex)
        , m_meaning(meaning)
        , m_codeRole(codeRole)
        , m_subsystem(subsystem)
        , m_runtimePlacement(runtimePlacement)
        , m_upstreamEquationIndices(upstreamIndices)
        , m_downstreamEquationIndices(downstreamIndices)
        , m_numUpstreamEquations(numUpstream)
        , m_numDownstreamEquations(numDownstream)
        , m_status(EQ_NOT_EVALUATED)
        , m_isEvaluated(false)
    {}
    
    virtual ~Equation() {}
    
    // Core interface - must be implemented by each equation
    virtual bool evaluate(EquationContext& ctx) = 0;
    
    // Validation - check if equation produced valid results
    virtual bool validate(const EquationContext& ctx) const = 0;
    
    // Getters
    int getNumber() const { return m_equationNumber; }
    const char* getTitle() const { return m_title; }
    const char* getLatex() const { return m_latex; }
    const char* getMeaning() const { return m_meaning; }
    const char* getCodeRole() const { return m_codeRole; }
    const char* getSubsystem() const { return m_subsystem; }
    const char* getRuntimePlacement() const { return m_runtimePlacement; }
    
    // Dependency access - scientific naming
    int getUpstreamEquationIndex(int i) const {
        return (m_upstreamEquationIndices && i >= 0 && i < m_numUpstreamEquations) 
               ? m_upstreamEquationIndices[i] : 0;
    }
    
    int getDownstreamEquationIndex(int i) const {
        return (m_downstreamEquationIndices && i >= 0 && i < m_numDownstreamEquations) 
               ? m_downstreamEquationIndices[i] : 0;
    }
    
    int getUpstreamEquationCount() const { return m_numUpstreamEquations; }
    int getDownstreamEquationCount() const { return m_numDownstreamEquations; }
    
    // Status
    EquationStatus getStatus() const { return m_status; }
    bool isEvaluated() const { return m_isEvaluated; }
    void markEvaluated(EquationStatus s) { m_status = s; m_isEvaluated = (s == EQ_EVALUATED_OK); }
    void reset() { m_status = EQ_NOT_EVALUATED; m_isEvaluated = false; }
    
    // Dependency checking
    bool hasUpstreamEquation(int eqNum) const {
        for(int i = 0; i < m_numUpstreamEquations; i++) {
            if(m_upstreamEquationIndices[i] == eqNum) return true;
        }
        return false;
    }
    
    bool hasDownstreamEquation(int eqNum) const {
        for(int i = 0; i < m_numDownstreamEquations; i++) {
            if(m_downstreamEquationIndices[i] == eqNum) return true;
        }
        return false;
    }
};

// ============================================================
// Equation Context (Data passed between equations)
// ============================================================
struct EquationData {
    float values[MAX_DATA_SIZE];
    size_t size;
    const char* name;
    
    EquationData() : size(0), name(nullptr) {
        memset(values, 0, sizeof(values));
    }
    
    void set(const char* n, const float* v, size_t s) {
        name = n;
        size = (s < MAX_DATA_SIZE) ? s : MAX_DATA_SIZE;
        memcpy(values, v, size * sizeof(float));
    }
    
    float get(size_t i) const {
        return (i < size) ? values[i] : 0.0f;
    }
};

class EquationContext {
private:
    // Storage for equation outputs (1-indexed)
    EquationData m_equationOutputs[101];
    
    // Global state accessible by all equations
    float m_phase;
    unsigned int m_seed;
    int m_width;
    int m_height;
    
    // Context vector components)
    float m_regimeState;
    float m_volatilityState;
    float m_trendState;
    float m_riskState;
    
    // Controller outputs)
    float m_archetypeWeights[K_ARCHETYPES];
    float m_softmaxTemperature;
    int m_selectedArchetypeIndex;
    
    // Archetype weights, 7)
    float m_firstLayerWeights[K_ARCHETYPES][NN_H * NN_IN];
    float m_firstLayerBiases[K_ARCHETYPES][NN_H];
    float m_secondLayerWeights[K_ARCHETYPES][NN_OUT * NN_H];
    float m_secondLayerBiases[K_ARCHETYPES][NN_OUT];
    
    // Frame buffer, 96)
    unsigned char* m_frameBuffer;  // RGBA, size = width*height*4
    
    // Diagnostics
    int m_equationsEvaluated;
    int m_equationsSkipped;
    int m_equationsFailed;

public:
    EquationContext()
        : m_phase(0.0f)
        , m_seed(1u)
        , m_width(640)
        , m_height(480)
        , m_regimeState(0.0f)
        , m_volatilityState(0.0f)
        , m_trendState(0.0f)
        , m_riskState(0.0f)
        , m_softmaxTemperature(1.0f)
        , m_selectedArchetypeIndex(0)
        , m_frameBuffer(nullptr)
        , m_equationsEvaluated(0)
        , m_equationsSkipped(0)
        , m_equationsFailed(0)
    {
        memset(m_archetypeWeights, 0, sizeof(m_archetypeWeights));
        memset(m_firstLayerWeights, 0, sizeof(m_firstLayerWeights));
        memset(m_firstLayerBiases, 0, sizeof(m_firstLayerBiases));
        memset(m_secondLayerWeights, 0, sizeof(m_secondLayerWeights));
        memset(m_secondLayerBiases, 0, sizeof(m_secondLayerBiases));
    }
    
    ~EquationContext() {
        if(m_frameBuffer) delete[] m_frameBuffer;
    }
    
    // Initialize frame buffer
    bool allocateFrameBuffer() {
        if(!m_frameBuffer) {
            m_frameBuffer = new unsigned char[m_width * m_height * 4];
            return m_frameBuffer != nullptr;
        }
        return true;
    }
    
    // Equation I/O
    void setOutput(int eqNum, const char* name, const float* values, size_t size) {
        if(eqNum >= 1 && eqNum <= 100) {
            m_equationOutputs[eqNum].set(name, values, size);
        }
    }
    
    const EquationData& getOutput(int eqNum) const {
        static EquationData empty;
        return (eqNum >= 1 && eqNum <= 100) ? m_equationOutputs[eqNum] : empty;
    }
    
    bool hasOutput(int eqNum) const {
        return (eqNum >= 1 && eqNum <= 100) && m_equationOutputs[eqNum].size > 0;
    }
    
    // Global state accessors - scientific naming
    float getPhase() const { return m_phase; }
    void setPhase(float phase) { m_phase = phase; }
    
    unsigned int getSeed() const { return m_seed; }
    void setSeed(unsigned int seed) { m_seed = seed; }
    
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    void setDimensions(int width, int height) { m_width = width; m_height = height; }
    
    // Context vector components) - scientific naming
    float getRegimeState() const { return m_regimeState; }
    float getVolatilityState() const { return m_volatilityState; }
    float getTrendState() const { return m_trendState; }
    float getRiskState() const { return m_riskState; }
    
    void setContext(float regime, float volatility, float trend, float risk) {
        m_regimeState = regime;
        m_volatilityState = volatility;
        m_trendState = trend;
        m_riskState = risk;
    }
    
    // Controller outputs) - scientific naming
    float getArchetypeWeight(int k) const {
        return (k >= 0 && k < K_ARCHETYPES) ? m_archetypeWeights[k] : 0.0f;
    }
    void setArchetypeWeights(const float* weights) {
        memcpy(m_archetypeWeights, weights, K_ARCHETYPES * sizeof(float));
    }
    float getSoftmaxTemperature() const { return m_softmaxTemperature; }
    void setSoftmaxTemperature(float temperature) { m_softmaxTemperature = temperature; }
    int getSelectedArchetypeIndex() const { return m_selectedArchetypeIndex; }
    void setSelectedArchetypeIndex(int k) { m_selectedArchetypeIndex = k; }
    
    // Archetype weights) - scientific naming
    void setArchetypeParams(int k, const float* W1, const float* b1,
                            const float* W2, const float* b2) {
        if(k >= 0 && k < K_ARCHETYPES) {
            memcpy(m_firstLayerWeights[k], W1, NN_H * NN_IN * sizeof(float));
            memcpy(m_firstLayerBiases[k], b1, NN_H * sizeof(float));
            memcpy(m_secondLayerWeights[k], W2, NN_OUT * NN_H * sizeof(float));
            memcpy(m_secondLayerBiases[k], b2, NN_OUT * sizeof(float));
        }
    }
    
    const float* getFirstLayerWeights(int k) const { 
        return (k >= 0 && k < K_ARCHETYPES) ? m_firstLayerWeights[k] : nullptr; 
    }
    const float* getFirstLayerBiases(int k) const { 
        return (k >= 0 && k < K_ARCHETYPES) ? m_firstLayerBiases[k] : nullptr; 
    }
    const float* getSecondLayerWeights(int k) const { 
        return (k >= 0 && k < K_ARCHETYPES) ? m_secondLayerWeights[k] : nullptr; 
    }
    const float* getSecondLayerBiases(int k) const { 
        return (k >= 0 && k < K_ARCHETYPES) ? m_secondLayerBiases[k] : nullptr; 
    }
    
    // Aliases for backward compatibility
    const float* getW1(int k) const { return getFirstLayerWeights(k); }
    const float* getB1(int k) const { return getFirstLayerBiases(k); }
    const float* getW2(int k) const { return getSecondLayerWeights(k); }
    const float* getB2(int k) const { return getSecondLayerBiases(k); }
    
    // Frame buffer)
    unsigned char* getFrameBuffer() { return m_frameBuffer; }
    const unsigned char* getFrameBuffer() const { return m_frameBuffer; }
    size_t getFrameBufferSize() const { return (size_t)m_width * m_height * 4; }
    
    // Diagnostics
    void recordEvaluation(bool success, bool skipped = false) {
        if(skipped) m_equationsSkipped++;
        else if(success) m_equationsEvaluated++;
        else m_equationsFailed++;
    }
    
    int getEquationsEvaluated() const { return m_equationsEvaluated; }
    int getEquationsSkipped() const { return m_equationsSkipped; }
    int getEquationsFailed() const { return m_equationsFailed; }
    
    // Validation helpers - scientific naming
    bool validateContextVector() const {
        return (m_regimeState >= -1.0f && m_regimeState <= 1.0f) &&
               (m_volatilityState >= -1.0f && m_volatilityState <= 1.0f) &&
               (m_trendState >= -1.0f && m_trendState <= 1.0f) &&
               (m_riskState >= -1.0f && m_riskState <= 1.0f);
    }
    
    bool validateArchetypeWeights() const {
        float sum = 0.0f;
        for(int k = 0; k < K_ARCHETYPES; k++) {
            if(m_archetypeWeights[k] < 0.0f || m_archetypeWeights[k] > 1.0f)
                return false;
            sum += m_archetypeWeights[k];
        }
        // Check normalization)
        float err = sum - 1.0f;
        return (err > -0.001f && err < 0.001f);
    }
    
    bool validateFrameBuffer() const {
        if(!m_frameBuffer) return false;
        return true;  // unsigned char can't be NaN
    }
};

}  // namespace EquationSystem

#endif
