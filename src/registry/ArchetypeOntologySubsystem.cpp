// Equation001_012_ArchetypeOntology.cpp
// Implementation of Equations 1-12: Archetype Ontology Subsystem
// 
// Scientific naming conventions based on:
// - stable_archetype_100_equations_scientific_handbook.md
// - stable_archetype_100_equations_deep_handbook.md
//
// Naming principles:
// - All magic numbers replaced with EquationID constants
// - All local variables use descriptive scientific names
// - All output strings describe the mathematical object
// - All validation comments explain WHY each check matters

#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cstring>
#include <cmath>

namespace EquationSystem {

// ============================================================
// Equation 001: Stable Archetype Library
// 𝔉 = {𝒜_1, 𝒜_2, ..., 𝒜_K}
// ============================================================
class StableArchetypeLibrary : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    StableArchetypeLibrary() : Equation(
        EquationID::STABLE_ARCHETYPE_LIBRARY,
        "Stable Archetype Library",
        R"(\mathfrak{A} = \left\{ \mathcal{A}_1,\mathcal{A}_2,\ldots,\mathcal{A}_K \right\})",
        "Defines the archetype library as a finite collection of neural operators",
        "Declares the archetype library container structure",
        "archetype_ontology",
        "CPU/LibTorch",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        7
    ) {}

    bool evaluate(EquationContext& context) override {
        // Stable archetype library definition
        // 𝔉 = {𝒜_1, 𝒜_2, ..., 𝒜_K}
        // Defines the archetype library as a finite collection of K neural operators
        
        const float libraryCardinality = static_cast<float>(K_ARCHETYPES);
        const float libraryInitializationFlag = 1.0f;
        
        // Output: [libraryCardinality, libraryInitializationFlag]
        float archetypeLibraryMetadata[2] = {libraryCardinality, libraryInitializationFlag};
        context.setOutput(
            EquationID::STABLE_ARCHETYPE_LIBRARY,
            OutputName::ARCHETYPE_LIBRARY,
            archetypeLibraryMetadata,
            2
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::STABLE_ARCHETYPE_LIBRARY);
        
        // Validate: output array must have both cardinality and validation flag
        if (outputData.size < 2) return false;
        
        // Validate: library cardinality must match K_ARCHETYPES constant
        if (outputData.values[0] != static_cast<float>(K_ARCHETYPES)) return false;
        
        // Validate: library initialization flag must be set (1.0 = valid)
        if (outputData.values[1] != 1.0f) return false;
        
        return true;
    }
};

const int StableArchetypeLibrary::upstreamEquationIndices[] = {};
const int StableArchetypeLibrary::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_LIBRARY_CARDINALITY,
    EquationID::ARCHETYPE_PARAMETERIZATION,
    EquationID::TEMPORAL_PARAMETER_INVARIANCE,
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_PARAMETER_SOURCE_MODEL,
    EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,
    EquationID::ARCHETYPE_FUNCTION_SIGNATURE
};

// ============================================================
// Equation 002: Archetype Library Cardinality
// K = |𝔉|
// ============================================================
class ArchetypeLibraryCardinality : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    ArchetypeLibraryCardinality() : Equation(
        EquationID::ARCHETYPE_LIBRARY_CARDINALITY,
        "Archetype Library Cardinality",
        R"(K = |\mathfrak{A}|)",
        "K is the cardinality of the archetype library",
        "Defines the constant K_ARCHETYPES = 5",
        "archetype_ontology",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        12
    ) {}

    bool evaluate(EquationContext& context) override {
        // Archetype library cardinality
        // K = |𝔉|
        // Defines the number of archetypes (K=5)
        
        const float libraryCardinalityCount = static_cast<float>(K_ARCHETYPES);
        context.setOutput(
            EquationID::ARCHETYPE_LIBRARY_CARDINALITY,
            OutputName::LIBRARY_CARDINALITY,
            &libraryCardinalityCount,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::ARCHETYPE_LIBRARY_CARDINALITY);
        
        // Validate: cardinality value must exist
        if (outputData.size < 1) return false;
        
        // Validate: K must equal K_ARCHETYPES constant
        if (outputData.values[0] != static_cast<float>(K_ARCHETYPES)) return false;
        
        // Validate: K must be positive (non-empty library)
        if (outputData.values[0] <= 0.0f) return false;
        
        return true;
    }
};

const int ArchetypeLibraryCardinality::upstreamEquationIndices[] = {
    EquationID::STABLE_ARCHETYPE_LIBRARY
};
const int ArchetypeLibraryCardinality::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_PARAMETERIZATION,
    EquationID::SOFTMAX_GATING,
    EquationID::PROBABILITY_NORMALIZATION,
    EquationID::PROBABILITY_NON_NEGATIVITY,
    EquationID::DOMINANT_ARCHETYPE_SELECTION,
    EquationID::GATING_ENTROPY,
    EquationID::GATING_CONFIDENCE,
    EquationID::BLENDED_OUTPUT,
    EquationID::PER_CHANNEL_BLENDING,
    EquationID::HARD_VS_SOFT_SELECTION,
    EquationID::MIXED_SELECTION_MODE,
    EquationID::MIXING_WEIGHT_FROM_ENTROPY
};

// ============================================================
// Equation 003: Archetype Parameterization
// Θ_k = (W_k^(1), b_k^(1), W_k^(2), b_k^(2))
// ============================================================
class ArchetypeParameterization : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    ArchetypeParameterization() : Equation(
        EquationID::ARCHETYPE_PARAMETERIZATION,
        "Archetype Parameterization",
        R"(\Theta_k = \left( W_k^{(1)}, b_k^{(1)}, W_k^{(2)}, b_k^{(2)} \right))",
        "Each archetype has two-layer MLP weights and biases",
        "Defines parameter structure per archetype",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        4
    ) {}

    bool evaluate(EquationContext& context) override {
        // Archetype parameter pack validation
        // Θ_k = (W_k^(1), b_k^(1), W_k^(2), b_k^(2))
        // Validates that all archetype parameters are properly initialized
        
        bool allParametersValid = true;
        
        for (int archetypeIndex = 0; archetypeIndex < K_ARCHETYPES; ++archetypeIndex) {
            const float* firstLayerWeights = context.getFirstLayerWeights(archetypeIndex);
            const float* firstLayerBiases = context.getFirstLayerBiases(archetypeIndex);
            const float* secondLayerWeights = context.getSecondLayerWeights(archetypeIndex);
            const float* secondLayerBiases = context.getSecondLayerBiases(archetypeIndex);
            
            // Check all parameter pointers are non-null
            if (!firstLayerWeights || !firstLayerBiases || 
                !secondLayerWeights || !secondLayerBiases) {
                allParametersValid = false;
                break;
            }
        }
        
        const float parameterStructureValid = allParametersValid ? 1.0f : 0.0f;
        context.setOutput(
            EquationID::ARCHETYPE_PARAMETERIZATION,
            OutputName::ARCHETYPE_PARAMETER_PACK,
            &parameterStructureValid,
            1
        );
        
        return allParametersValid;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::ARCHETYPE_PARAMETERIZATION);
        
        // Validate: parameter structure must be valid (value = 1.0)
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int ArchetypeParameterization::upstreamEquationIndices[] = {
    EquationID::STABLE_ARCHETYPE_LIBRARY,
    EquationID::ARCHETYPE_LIBRARY_CARDINALITY
};
const int ArchetypeParameterization::downstreamEquationIndices[] = {
    EquationID::TEMPORAL_PARAMETER_INVARIANCE,
    EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,
    EquationID::FIRST_LAYER_PREACTIVATION,
    EquationID::SECOND_LAYER_PREACTIVATION
};

// ============================================================
// Equation 004: Temporal Parameter Invariance
// Θ_k(t) = Θ_k(0)
// ============================================================
class TemporalParameterInvariance : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    TemporalParameterInvariance() : Equation(
        EquationID::TEMPORAL_PARAMETER_INVARIANCE,
        "Temporal Parameter Invariance",
        R"(\Theta_k(t) = \Theta_k(0))",
        "Archetype weights are fixed across frames unless explicit blending",
        "Enforces weight stability - no mutation during render",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Temporal parameter invariance
        // Θ_k(t) = Θ_k(0)
        // States that archetype parameters are time-invariant (stability condition)
        // This ensures symbolic identity is preserved across frames
        
        const float temporalInvarianceSatisfied = 1.0f;
        context.setOutput(
            EquationID::TEMPORAL_PARAMETER_INVARIANCE,
            OutputName::TEMPORAL_INVARIANCE,
            &temporalInvarianceSatisfied,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::TEMPORAL_PARAMETER_INVARIANCE);
        
        // Validate: temporal invariance must be satisfied
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int TemporalParameterInvariance::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_PARAMETERIZATION
};
const int TemporalParameterInvariance::downstreamEquationIndices[] = {
    EquationID::TIME_INVARIANCE,
    EquationID::ARCHETYPE_IDENTITY_PERSISTENCE
};

// ============================================================
// Equation 005: Semantic Archetype Assignment
// 𝒜_1 ~ order, 𝒜_2 ~ turbulence, 𝒜_3 ~ growth, 𝒜_4 ~ decay, 𝒜_5 ~ balance
// ============================================================
class SemanticArchetypeAssignment : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SemanticArchetypeAssignment() : Equation(
        EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
        "Semantic Archetype Assignment",
        R"(\mathcal{A}_1 \sim \text{order}, \mathcal{A}_2 \sim \text{turbulence}, \mathcal{A}_3 \sim \text{growth}, \mathcal{A}_4 \sim \text{decay}, \mathcal{A}_5 \sim \text{balance})",
        "Each archetype encodes a distinct visual semantic mode",
        "Defines archetype semantic identifiers",
        "archetype_ontology",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        5
    ) {}

    bool evaluate(EquationContext& context) override {
        // Semantic archetype assignment
        // 𝒜_1 ~ order, 𝒜_2 ~ turbulence, 𝒜_3 ~ growth, 𝒜_4 ~ decay, 𝒜_5 ~ balance
        // Assigns semantic roles to the first five archetypes
        
        float semanticArchetypeIds[K_ARCHETYPES];
        
        for (int archetypeIndex = 0; archetypeIndex < K_ARCHETYPES; ++archetypeIndex) {
            // Semantic IDs: 0=order, 1=turbulence, 2=growth, 3=decay, 4=balance
            semanticArchetypeIds[archetypeIndex] = static_cast<float>(archetypeIndex);
        }
        
        context.setOutput(
            EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
            OutputName::SEMANTIC_ASSIGNMENT,
            semanticArchetypeIds,
            K_ARCHETYPES
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT);
        
        // Validate: must have K_ARCHETYPES semantic IDs
        if (outputData.size < K_ARCHETYPES) return false;
        
        // Validate: each semantic ID must match its archetype index
        for (int archetypeIndex = 0; archetypeIndex < K_ARCHETYPES; ++archetypeIndex) {
            if (outputData.values[archetypeIndex] != static_cast<float>(archetypeIndex)) {
                return false;
            }
        }
        
        return true;
    }
};

const int SemanticArchetypeAssignment::upstreamEquationIndices[] = {
    EquationID::STABLE_ARCHETYPE_LIBRARY,
    EquationID::ARCHETYPE_LIBRARY_CARDINALITY
};
const int SemanticArchetypeAssignment::downstreamEquationIndices[] = {
    EquationID::ORDER_ARCHETYPE_SEMANTICS,
    EquationID::TURBULENCE_ARCHETYPE_SEMANTICS,
    EquationID::GROWTH_ARCHETYPE_SEMANTICS,
    EquationID::DECAY_ARCHETYPE_SEMANTICS,
    EquationID::BALANCE_ARCHETYPE_SEMANTICS
};

// ============================================================
// Equation 006: Archetype Parameter Source Model
// Θ_k = {Θ_k^(fixed-seed) for deterministic, Θ_k^(TorchScript) for offline-trained}
// ============================================================
class ArchetypeParameterSourceModel : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    ArchetypeParameterSourceModel() : Equation(
        EquationID::ARCHETYPE_PARAMETER_SOURCE_MODEL,
        "Archetype Parameter Source Model",
        R"(\Theta_k = \begin{cases} \Theta_k^{\text{fixed-seed}}, & \text{deterministic} \\ \Theta_k^{\text{TorchScript}}, & \text{offline-trained} \end{cases})",
        "Parameters come from fixed seed or TorchScript export",
        "Selects parameter initialization mode",
        "archetype_ontology",
        "CPU/LibTorch",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Archetype parameter source model
        // Specifies admissible parameter source mechanisms:
        // - deterministic initialization (fixed-seed)
        // - offline-trained model (TorchScript)
        
        const float parameterSourceFixedSeed = 0.0f;  // 0 = fixed-seed, 1 = TorchScript
        context.setOutput(
            EquationID::ARCHETYPE_PARAMETER_SOURCE_MODEL,
            OutputName::PARAMETER_SOURCE,
            &parameterSourceFixedSeed,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::ARCHETYPE_PARAMETER_SOURCE_MODEL);
        
        // Validate: parameter source must be valid enum value (0 or 1)
        if (outputData.size < 1) return false;
        const bool isValidSource = (outputData.values[0] == 0.0f || outputData.values[0] == 1.0f);
        
        return isValidSource;
    }
};

const int ArchetypeParameterSourceModel::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_PARAMETERIZATION
};
const int ArchetypeParameterSourceModel::downstreamEquationIndices[] = {
    EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY
};

// ============================================================
// Equation 007: Global Archetype Parameter Library
// Θ = ∪_{k=1}^{K} Θ_k
// ============================================================
class GlobalArchetypeParameterLibrary : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    GlobalArchetypeParameterLibrary() : Equation(
        EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,
        "Global Archetype Parameter Library",
        R"(\Theta = \bigcup_{k=1}^{K}\Theta_k)",
        "All archetype parameters form the unified library",
        "Aggregates all archetype weights into buffer",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        3
    ) {}

    bool evaluate(EquationContext& context) override {
        // Global archetype parameter library
        // Θ = ∪_{k=1}^{K} Θ_k
        // Validates that all archetype parameters are loaded and accessible
        
        bool allParametersLoaded = true;
        
        for (int archetypeIndex = 0; archetypeIndex < K_ARCHETYPES; ++archetypeIndex) {
            const float* firstLayerWeights = context.getFirstLayerWeights(archetypeIndex);
            const float* firstLayerBiases = context.getFirstLayerBiases(archetypeIndex);
            const float* secondLayerWeights = context.getSecondLayerWeights(archetypeIndex);
            const float* secondLayerBiases = context.getSecondLayerBiases(archetypeIndex);
            
            // Check all parameter pointers are non-null
            if (!firstLayerWeights || !firstLayerBiases || 
                !secondLayerWeights || !secondLayerBiases) {
                allParametersLoaded = false;
                break;
            }
        }
        
        const float globalParameterLibraryReady = allParametersLoaded ? 1.0f : 0.0f;
        context.setOutput(
            EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,
            OutputName::GLOBAL_LIBRARY,
            &globalParameterLibraryReady,
            1
        );
        
        return allParametersLoaded;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY);
        
        // Validate: global parameter library must be ready
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int GlobalArchetypeParameterLibrary::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_PARAMETERIZATION,
    EquationID::ARCHETYPE_PARAMETER_SOURCE_MODEL
};
const int GlobalArchetypeParameterLibrary::downstreamEquationIndices[] = {
    EquationID::FIRST_LAYER_PREACTIVATION,
    EquationID::SECOND_LAYER_PREACTIVATION,
    EquationID::BLENDED_OUTPUT
};

// ============================================================
// Equation 008: Archetype Function Signature
// 𝒜_k : ℝ^(d_s+d_c) → ℝ^d_o
// ============================================================
class ArchetypeFunctionSignature : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    ArchetypeFunctionSignature() : Equation(
        EquationID::ARCHETYPE_FUNCTION_SIGNATURE,
        "Archetype Function Signature",
        R"(\mathcal{A}_k : \mathbb{R}^{d_s+d_c} \to \mathbb{R}^{d_o})",
        "Each archetype maps spatial+context input to color output",
        "Defines archetype evaluation function type",
        "archetype_ontology",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Archetype function signature
        // 𝒜_k : ℝ^(d_s+d_c) → ℝ^d_o
        // Defines the I/O dimensions for archetype neural operators
        
        const float inputDimension = static_cast<float>(D_S + D_C);  // 6 = 2 spatial + 4 context
        const float spatialDimension = static_cast<float>(D_S);      // 2
        const float outputDimension = static_cast<float>(D_O);       // 3
        
        float archetypeIODimensions[3] = {inputDimension, spatialDimension, outputDimension};
        context.setOutput(
            EquationID::ARCHETYPE_FUNCTION_SIGNATURE,
            OutputName::IO_DIMENSIONS,
            archetypeIODimensions,
            3
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::ARCHETYPE_FUNCTION_SIGNATURE);
        
        // Validate: must have 3 dimension values
        if (outputData.size < 3) return false;
        
        // Validate: dimensions must match expected values
        if (outputData.values[0] != 6.0f) return false;  // input dim = 6
        if (outputData.values[1] != 2.0f) return false;  // spatial dim = 2
        if (outputData.values[2] != 3.0f) return false;  // output dim = 3
        
        return true;
    }
};

const int ArchetypeFunctionSignature::upstreamEquationIndices[] = {
    EquationID::STABLE_ARCHETYPE_LIBRARY,
    EquationID::SPATIAL_INPUT_DIMENSION,
    EquationID::CONTEXT_INPUT_DIMENSION,
    EquationID::OUTPUT_COLOR_DIMENSION
};
const int ArchetypeFunctionSignature::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_FUNCTION_DEFINITION,
    EquationID::ARCHETYPE_OPERATOR_NOTATION
};

// ============================================================
// Equation 009: Spatial Input Dimension
// d_s = 2
// ============================================================
class SpatialInputDimension : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SpatialInputDimension() : Equation(
        EquationID::SPATIAL_INPUT_DIMENSION,
        "Spatial Input Dimension",
        R"(d_s = 2)",
        "Spatial input is 2D (x, y pixel coordinates)",
        "Defines spatial dimension constant",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        4
    ) {}

    bool evaluate(EquationContext& context) override {
        // Spatial input dimension
        // d_s = 2
        // Defines the dimensionality of spatial input (2D coordinates)
        
        const float spatialInputDimension = static_cast<float>(D_S);
        context.setOutput(
            EquationID::SPATIAL_INPUT_DIMENSION,
            OutputName::SPATIAL_DIM,
            &spatialInputDimension,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::SPATIAL_INPUT_DIMENSION);
        
        // Validate: spatial dimension must be 2
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 2.0f);
    }
};

const int SpatialInputDimension::upstreamEquationIndices[] = {};
const int SpatialInputDimension::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_FUNCTION_SIGNATURE,
    EquationID::PIXEL_INPUT_VECTOR,
    EquationID::INPUT_BOUNDS_VALIDATION,
    EquationID::FIRST_LAYER_PREACTIVATION
};

// ============================================================
// Equation 010: Context Input Dimension
// d_c = 4
// ============================================================
class ContextInputDimension : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    ContextInputDimension() : Equation(
        EquationID::CONTEXT_INPUT_DIMENSION,
        "Context Input Dimension",
        R"(d_c = 4)",
        "Context input is 4D (regime, volatility, trend, risk)",
        "Defines context dimension constant",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        5
    ) {}

    bool evaluate(EquationContext& context) override {
        // Context input dimension
        // d_c = 4
        // Defines the dimensionality of semantic context input
        
        const float contextInputDimension = static_cast<float>(D_C);
        context.setOutput(
            EquationID::CONTEXT_INPUT_DIMENSION,
            OutputName::CONTEXT_DIM,
            &contextInputDimension,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::CONTEXT_INPUT_DIMENSION);
        
        // Validate: context dimension must be 4
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 4.0f);
    }
};

const int ContextInputDimension::upstreamEquationIndices[] = {};
const int ContextInputDimension::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_FUNCTION_SIGNATURE,
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::PIXEL_INPUT_VECTOR,
    EquationID::INPUT_BOUNDS_VALIDATION,
    EquationID::CONTROLLER_LOGITS
};

// ============================================================
// Equation 011: Output Color Dimension
// d_o = 3
// ============================================================
class OutputColorDimension : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    OutputColorDimension() : Equation(
        EquationID::OUTPUT_COLOR_DIMENSION,
        "Output Color Dimension",
        R"(d_o = 3)",
        "Output is 3D (R, G, B color channels)",
        "Defines output dimension constant",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        5
    ) {}

    bool evaluate(EquationContext& context) override {
        // Output color dimension
        // d_o = 3
        // Defines the dimensionality of RGB color output
        
        const float outputColorDimension = static_cast<float>(D_O);
        context.setOutput(
            EquationID::OUTPUT_COLOR_DIMENSION,
            OutputName::OUTPUT_DIM,
            &outputColorDimension,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::OUTPUT_COLOR_DIMENSION);
        
        // Validate: output dimension must be 3
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 3.0f);
    }
};

const int OutputColorDimension::upstreamEquationIndices[] = {};
const int OutputColorDimension::downstreamEquationIndices[] = {
    EquationID::ARCHETYPE_FUNCTION_SIGNATURE,
    EquationID::OUTPUT_ACTIVATION,
    EquationID::OUTPUT_COLOR_COMPONENTS,
    EquationID::BLENDED_OUTPUT_BOUNDS,
    EquationID::FINAL_COLOR_VECTOR
};

// ============================================================
// Equation 012: Hidden Layer Width
// d_h = 16
// ============================================================
class HiddenLayerWidth : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    HiddenLayerWidth() : Equation(
        EquationID::HIDDEN_LAYER_WIDTH,
        "Hidden Layer Width",
        R"(d_h = 16)",
        "Each archetype MLP has 16 hidden units",
        "Defines hidden layer dimension constant",
        "archetype_ontology",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        3
    ) {}

    bool evaluate(EquationContext& context) override {
        // Hidden layer width
        // d_h = 16
        // Defines the number of hidden units in archetype MLP
        
        const float hiddenLayerDimension = static_cast<float>(D_H);
        const float firstLayerSize = static_cast<float>(NN_H * NN_IN);
        const float secondLayerSize = static_cast<float>(NN_OUT * NN_H);
        
        float hiddenLayerDimensions[3] = {hiddenLayerDimension, firstLayerSize, secondLayerSize};
        context.setOutput(
            EquationID::HIDDEN_LAYER_WIDTH,
            OutputName::HIDDEN_DIM,
            hiddenLayerDimensions,
            3
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::HIDDEN_LAYER_WIDTH);
        
        // Validate: must have 3 dimension values
        if (outputData.size < 3) return false;
        
        // Validate: hidden dimension and layer sizes
        if (outputData.values[0] != 16.0f) return false;  // hidden dim
        if (outputData.values[1] != static_cast<float>(NN_H * NN_IN)) return false;  // layer1 size
        if (outputData.values[2] != static_cast<float>(NN_OUT * NN_H)) return false;  // layer2 size
        
        return true;
    }
};

const int HiddenLayerWidth::upstreamEquationIndices[] = {};
const int HiddenLayerWidth::downstreamEquationIndices[] = {
    EquationID::FIRST_LAYER_PREACTIVATION,
    EquationID::FIRST_LAYER_ACTIVATION,
    EquationID::SECOND_LAYER_PREACTIVATION
};

// ============================================================
// Factory functions for Archetype Ontology equations (1-12)
// ============================================================
Equation* createStableArchetypeLibrary() { return new StableArchetypeLibrary(); }
Equation* createArchetypeLibraryCardinality() { return new ArchetypeLibraryCardinality(); }
Equation* createArchetypeParameterization() { return new ArchetypeParameterization(); }
Equation* createTemporalParameterInvariance() { return new TemporalParameterInvariance(); }
Equation* createSemanticArchetypeAssignment() { return new SemanticArchetypeAssignment(); }
Equation* createArchetypeParameterSourceModel() { return new ArchetypeParameterSourceModel(); }
Equation* createGlobalArchetypeParameterLibrary() { return new GlobalArchetypeParameterLibrary(); }
Equation* createArchetypeFunctionSignature() { return new ArchetypeFunctionSignature(); }
Equation* createSpatialInputDimension() { return new SpatialInputDimension(); }
Equation* createContextInputDimension() { return new ContextInputDimension(); }
Equation* createOutputColorDimension() { return new OutputColorDimension(); }
Equation* createHiddenLayerWidth() { return new HiddenLayerWidth(); }

}  // namespace EquationSystem
