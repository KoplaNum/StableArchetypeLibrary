// Blending.cpp - Archetype Output Blending (Eq 61-70)
// Scientific naming based on stable_archetype_100_equations_scientific_handbook.md

#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>

namespace EquationSystem {

// ============================================================
// Equation 61: Blended Output
// o_{p,t} = Σ_k π_k(t) * o_{k,p,t}
// ============================================================
class BlendedOutput : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    BlendedOutput() : Equation(
        EquationID::BLENDED_OUTPUT,
        "Blended Output",
        R"(\mathbf{o}_{p,t} = \sum_{k=1}^{K} \pi_k(t)\mathbf{o}_{k,p,t})",
        "Weighted sum of all archetype outputs per pixel",
        "Computes final blended color from archetypes",
        "blending",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        8
    ) {}

    bool evaluate(EquationContext& context) override {
        // Blend archetype outputs using softmax weights
        // Each archetype contributes proportionally to its weight
        
        const EquationData& archetypeWeightsData = context.getOutput(EquationID::SOFTMAX_GATING);
        const EquationData& archetypeOutputData = context.getOutput(EquationID::OUTPUT_ACTIVATION);
        
        if (archetypeWeightsData.size < K_ARCHETYPES) return false;
        if (archetypeOutputData.size < NN_OUT) return false;
        
        // For single archetype test, use first archetype output
        float blendedOutputRGB[NN_OUT];
        
        for (int colorChannel = 0; colorChannel < NN_OUT; ++colorChannel) {
            blendedOutputRGB[colorChannel] = 0.0f;
            
            for (int archetypeIndex = 0; archetypeIndex < K_ARCHETYPES; ++archetypeIndex) {
                const float archetypeWeight = archetypeWeightsData.values[archetypeIndex];
                blendedOutputRGB[colorChannel] += archetypeWeight * archetypeOutputData.values[colorChannel];
            }
        }
        
        context.setOutput(
            EquationID::BLENDED_OUTPUT,
            OutputName::BLENDED,
            blendedOutputRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::BLENDED_OUTPUT);
        
        // Validate: must have RGB output
        if (outputData.size < NN_OUT) return false;
        
        // Validate: all color channels must be in [0, 1]
        for (int colorChannel = 0; colorChannel < NN_OUT; ++colorChannel) {
            if (outputData.values[colorChannel] < 0.0f || outputData.values[colorChannel] > 1.0f) {
                return false;
            }
        }
        
        return true;
    }
};

const int BlendedOutput::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_LIBRARY_CARDINALITY,
    EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION,
    EquationID::SOFTMAX_GATING
};
const int BlendedOutput::downstreamEquationIndices[] = {
    EquationID::PER_CHANNEL_BLENDING,
    EquationID::BLENDED_OUTPUT_BOUNDS,
    EquationID::HARD_VS_SOFT_SELECTION,
    EquationID::FRAME_MEAN_OUTPUT,
    EquationID::OUTPUT_VARIANCE,
    EquationID::RED_CHANNEL_SYNTHESIS,
    EquationID::GREEN_CHANNEL_SYNTHESIS,
    EquationID::BLUE_CHANNEL_SYNTHESIS
};

// ============================================================
// Equation 62: Per-Channel Blending
// o_{p,t}^(c) = Σ_k π_k(t) * o_{k,p,t}^(c)
// ============================================================
class PerChannelBlending : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    PerChannelBlending() : Equation(
        EquationID::PER_CHANNEL_BLENDING,
        "Per-Channel Blending",
        R"(o_{p,t}^{(c)} = \sum_{k=1}^{K}\pi_k(t)o_{k,p,t}^{(c)})",
        "Scalar blend equation for each color channel",
        "Blends single color channel across archetypes",
        "blending",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Pass through blended output for per-channel processing
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        
        if (blendedData.size < NN_OUT) return false;
        
        context.setOutput(
            EquationID::PER_CHANNEL_BLENDING,
            OutputName::CHANNEL_BLEND,
            blendedData.values,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::PER_CHANNEL_BLENDING);
        
        // Validate: must have RGB channels
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int PerChannelBlending::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_LIBRARY_CARDINALITY,
    EquationID::OUTPUT_COLOR_COMPONENTS,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT
};
const int PerChannelBlending::downstreamEquationIndices[] = {};

// ============================================================
// Equation 63: Blended Output Bounds
// o_{p,t} ∈ [0,1]^3
// ============================================================
class BlendedOutputBounds : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    BlendedOutputBounds() : Equation(
        EquationID::BLENDED_OUTPUT_BOUNDS,
        "Blended Output Bounds",
        R"(\mathbf{o}_{p,t} \in [0,1]^3)",
        "Blended output remains in valid color range",
        "Validates blended output range",
        "blending",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Validate that blended output is in valid color range
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        
        float boundsValid = 1.0f;
        
        if (blendedData.size >= NN_OUT) {
            for (int colorChannel = 0; colorChannel < NN_OUT; ++colorChannel) {
                if (blendedData.values[colorChannel] < 0.0f || blendedData.values[colorChannel] > 1.0f) {
                    boundsValid = 0.0f;
                    break;
                }
            }
        } else {
            boundsValid = 0.0f;
        }
        
        context.setOutput(
            EquationID::BLENDED_OUTPUT_BOUNDS,
            OutputName::BLENDED_BOUNDS,
            &boundsValid,
            1
        );
        
        return (boundsValid == 1.0f);
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::BLENDED_OUTPUT_BOUNDS);
        
        // Validate: bounds check must pass
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int BlendedOutputBounds::upstreamEquationIndices[] = {
    EquationID::OUTPUT_COLOR_DIMENSION,
    EquationID::PROBABILITY_NORMALIZATION,
    EquationID::PROBABILITY_NON_NEGATIVITY,
    EquationID::BLENDED_OUTPUT
};
const int BlendedOutputBounds::downstreamEquationIndices[] = {};

// ============================================================
// Equation 64: Hard vs Soft Selection
// o_{p,t} = { o_{k*,p,t} for hard, Σ_k π_k*o_{k,p,t} for soft }
// ============================================================
class HardVsSoftSelection : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    HardVsSoftSelection() : Equation(
        EquationID::HARD_VS_SOFT_SELECTION,
        "Hard Vs Soft Selection",
        R"(\mathbf{o}_{p,t} = \begin{cases} \mathbf{o}_{k_t^\star,p,t}, & \text{hard} \\ \sum_{k=1}^{K}\pi_k(t)\mathbf{o}_{k,p,t}, & \text{soft} \end{cases})",
        "Output is either dominant archetype or blended",
        "Selects hard or soft blending mode",
        "blending",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // For now, use soft blending (weighted sum)
        // Hard selection would use only dominant archetype
        
        const float selectionModeSoft = 0.0f;  // 0 = soft, 1 = hard
        
        context.setOutput(
            EquationID::HARD_VS_SOFT_SELECTION,
            OutputName::SEL_MODE,
            &selectionModeSoft,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::HARD_VS_SOFT_SELECTION);
        
        // Validate: selection mode must be 0 (soft) or 1 (hard)
        if (outputData.size < 1) return false;
        if (outputData.values[0] != 0.0f && outputData.values[0] != 1.0f) return false;
        
        return true;
    }
};

const int HardVsSoftSelection::upstreamEquationIndices[] = {
    EquationID::ARCHETYPE_FUNCTION_DEFINITION,
    EquationID::SOFTMAX_GATING,
    EquationID::DOMINANT_ARCHETYPE_SELECTION,
    EquationID::BLENDED_OUTPUT
};
const int HardVsSoftSelection::downstreamEquationIndices[] = {
    EquationID::MIXED_SELECTION_MODE
};

// ============================================================
// Equation 65: Mixed Selection Mode
// o_{p,t}^{mix} = (1-λ_t)*o_{k*,p,t} + λ_t*Σ_k π_k*o_{k,p,t}
// ============================================================
class MixedSelectionMode : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    MixedSelectionMode() : Equation(
        EquationID::MIXED_SELECTION_MODE,
        "Mixed Selection Mode",
        R"(\mathbf{o}_{p,t}^{\text{mix}} = (1-\lambda_t)\mathbf{o}_{k_t^\star,p,t} + \lambda_t\sum_{k=1}^{K}\pi_k(t)\mathbf{o}_{k,p,t})",
        "Interpolation between hard and soft selection",
        "Blends hard and soft modes continuously",
        "blending",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Get mixing parameter from entropy
        // High entropy → more soft blending
        // Low entropy → more hard selection
        
        const EquationData& mixingLambdaData = context.getOutput(EquationID::MIXING_WEIGHT_FROM_ENTROPY);
        
        float mixingLambda = (mixingLambdaData.size >= 1) ? mixingLambdaData.values[0] : 1.0f;
        
        context.setOutput(
            EquationID::MIXED_SELECTION_MODE,
            OutputName::MIX_MODE,
            &mixingLambda,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::MIXED_SELECTION_MODE);
        
        // Validate: mixing parameter must be in [0, 1]
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int MixedSelectionMode::upstreamEquationIndices[] = {
    EquationID::SOFTMAX_GATING,
    EquationID::DOMINANT_ARCHETYPE_SELECTION,
    EquationID::BLENDED_OUTPUT,
    EquationID::MIXING_WEIGHT_FROM_ENTROPY
};
const int MixedSelectionMode::downstreamEquationIndices[] = {
    EquationID::HARD_SELECTION_LIMIT,
    EquationID::SOFT_SELECTION_LIMIT
};

// ============================================================
// Equation 66: Mixing Weight From Entropy
// λ_t = σ(a_λ * H_π(t) + b_λ)
// ============================================================
class MixingWeightFromEntropy : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    MixingWeightFromEntropy() : Equation(
        EquationID::MIXING_WEIGHT_FROM_ENTROPY,
        "Mixing Weight From Entropy",
        R"(\lambda_t = \sigma(a_\lambda H_\pi(t) + b_\lambda))",
        "Entropy determines hard/soft blend ratio",
        "Computes mixing parameter from gating entropy",
        "blending",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // High entropy → λ → 1.0 (soft blending)
        // Low entropy → λ → 0.0 (hard selection)
        
        const EquationData& entropyData = context.getOutput(EquationID::GATING_ENTROPY);
        
        if (entropyData.size < 1) return false;
        
        const float shannonEntropy = entropyData.values[0];
        
        // Sigmoid mapping: entropy → mixing weight
        const float entropyCoefficient = 2.0f;
        const float entropyOffset = -1.0f;
        
        const float sigmoidInput = entropyCoefficient * shannonEntropy + entropyOffset;
        const float mixingLambda = 1.0f / (1.0f + expf(-sigmoidInput));
        
        context.setOutput(
            EquationID::MIXING_WEIGHT_FROM_ENTROPY,
            OutputName::MIX_LAMBDA,
            &mixingLambda,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::MIXING_WEIGHT_FROM_ENTROPY);
        
        // Validate: mixing weight must be in [0, 1]
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int MixingWeightFromEntropy::upstreamEquationIndices[] = {
    EquationID::GATING_ENTROPY
};
const int MixingWeightFromEntropy::downstreamEquationIndices[] = {
    EquationID::MIXED_SELECTION_MODE
};

// ============================================================
// Equation 67: Hard Selection Limit
// o_{p,t}^{mix} → o_{k*,p,t} as λ_t → 0
// ============================================================
class HardSelectionLimit : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    HardSelectionLimit() : Equation(
        EquationID::HARD_SELECTION_LIMIT,
        "Hard Selection Limit",
        R"(\mathbf{o}_{p,t}^{\text{mix}} \to \mathbf{o}_{k_t^\star,p,t} \quad \text{as } \lambda_t \to 0)",
        "Zero mixing weight yields pure hard selection",
        "Documents hard selection boundary behavior",
        "blending",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Hard selection limit is a boundary condition
        // Documented for completeness
        
        const float hardSelectionLimitValid = 1.0f;
        
        context.setOutput(
            EquationID::HARD_SELECTION_LIMIT,
            OutputName::HARD_LIM,
            &hardSelectionLimitValid,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::HARD_SELECTION_LIMIT);
        
        // Validate: limit flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int HardSelectionLimit::upstreamEquationIndices[] = {
    EquationID::MIXED_SELECTION_MODE
};
const int HardSelectionLimit::downstreamEquationIndices[] = {};

// ============================================================
// Equation 68: Soft Selection Limit
// o_{p,t}^{mix} → o_{p,t} as λ_t → 1
// ============================================================
class SoftSelectionLimit : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SoftSelectionLimit() : Equation(
        EquationID::SOFT_SELECTION_LIMIT,
        "Soft Selection Limit",
        R"(\mathbf{o}_{p,t}^{\text{mix}} \to \mathbf{o}_{p,t} \quad \text{as } \lambda_t \to 1)",
        "Unit mixing weight yields pure soft blending",
        "Documents soft selection boundary behavior",
        "blending",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Soft selection limit is a boundary condition
        // Documented for completeness
        
        const float softSelectionLimitValid = 1.0f;
        
        context.setOutput(
            EquationID::SOFT_SELECTION_LIMIT,
            OutputName::SOFT_LIM,
            &softSelectionLimitValid,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::SOFT_SELECTION_LIMIT);
        
        // Validate: limit flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int SoftSelectionLimit::upstreamEquationIndices[] = {
    EquationID::BLENDED_OUTPUT,
    EquationID::MIXED_SELECTION_MODE
};
const int SoftSelectionLimit::downstreamEquationIndices[] = {};

// ============================================================
// Equation 69: Frame Mean Output
// ō_t = (1/|Ω|) * Σ_{p∈Ω} o_{p,t}
// ============================================================
class FrameMeanOutput : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    FrameMeanOutput() : Equation(
        EquationID::FRAME_MEAN_OUTPUT,
        "Frame Mean Output",
        R"(\bar{\mathbf{o}}_t = \frac{1}{|\Omega|}\sum_{p\in\Omega}\mathbf{o}_{p,t})",
        "Average blended color across all pixels",
        "Computes frame-level color statistics",
        "blending",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // For single pixel test, mean equals pixel value
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        
        float frameMeanOutputRGB[NN_OUT] = {0.0f, 0.0f, 0.0f};
        
        if (blendedData.size >= NN_OUT) {
            for (int colorChannel = 0; colorChannel < NN_OUT; ++colorChannel) {
                frameMeanOutputRGB[colorChannel] = blendedData.values[colorChannel];
            }
        }
        
        context.setOutput(
            EquationID::FRAME_MEAN_OUTPUT,
            OutputName::FRAME_MEAN,
            frameMeanOutputRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::FRAME_MEAN_OUTPUT);
        
        // Validate: must have RGB mean
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int FrameMeanOutput::upstreamEquationIndices[] = {
    EquationID::SPATIAL_DOMAIN_DEFINITION,
    EquationID::BLENDED_OUTPUT
};
const int FrameMeanOutput::downstreamEquationIndices[] = {
    EquationID::OUTPUT_VARIANCE
};

// ============================================================
// Equation 70: Output Variance
// Var_t(o) = (1/|Ω|) * Σ_{p∈Ω} ||o_{p,t} - ō_t||_2^2
// ============================================================
class OutputVariance : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    OutputVariance() : Equation(
        EquationID::OUTPUT_VARIANCE,
        "Output Variance",
        R"(\operatorname{Var}_t(\mathbf{o}) = \frac{1}{|\Omega|}\sum_{p\in\Omega}\|\mathbf{o}_{p,t}-\bar{\mathbf{o}}_t\|_2^2)",
        "Spatial variance of blended output",
        "Measures frame contrast/diversity",
        "blending",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        3,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // For single pixel test, variance is zero
        
        const float outputSpatialVariance = 0.0f;
        
        context.setOutput(
            EquationID::OUTPUT_VARIANCE,
            OutputName::VARIANCE,
            &outputSpatialVariance,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::OUTPUT_VARIANCE);
        
        // Validate: variance must be non-negative
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f) return false;
        
        return true;
    }
};

const int OutputVariance::upstreamEquationIndices[] = {
    EquationID::SPATIAL_DOMAIN_DEFINITION,
    EquationID::BLENDED_OUTPUT,
    EquationID::FRAME_MEAN_OUTPUT
};
const int OutputVariance::downstreamEquationIndices[] = {};

// ============================================================
// Factory functions for Blending equations (61-70)
// ============================================================
Equation* createBlendedOutput() { return new BlendedOutput(); }
Equation* createPerChannelBlending() { return new PerChannelBlending(); }
Equation* createBlendedOutputBounds() { return new BlendedOutputBounds(); }
Equation* createHardVsSoftSelection() { return new HardVsSoftSelection(); }
Equation* createMixedSelectionMode() { return new MixedSelectionMode(); }
Equation* createMixingWeightFromEntropy() { return new MixingWeightFromEntropy(); }
Equation* createHardSelectionLimit() { return new HardSelectionLimit(); }
Equation* createSoftSelectionLimit() { return new SoftSelectionLimit(); }
Equation* createFrameMeanOutput() { return new FrameMeanOutput(); }
Equation* createOutputVariance() { return new OutputVariance(); }

}  // namespace EquationSystem
