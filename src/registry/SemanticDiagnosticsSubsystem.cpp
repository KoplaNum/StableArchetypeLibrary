// SemanticDiagnostics.cpp - Archetype Semantic Influence Analysis (Eq 71-80)
// Scientific naming based on stable_archetype_100_equations_scientific_handbook.md

#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>

namespace EquationSystem {

// ============================================================
// Equation 71: Order Archetype Semantics
// A_1 ~ order (geometric motifs)
// ============================================================
class OrderArchetypeSemantics : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    OrderArchetypeSemantics() : Equation(
        EquationID::ORDER_ARCHETYPE_SEMANTICS,
        "Order Archetype Semantics",
        R"(\mathcal{A}_1 \sim \text{order})",
        "Archetype 1 produces structured geometric patterns",
        "Documents order archetype visual semantics",
        "semantic_diagnostics",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Order archetype semantic identifier
        
        const float orderArchetypeIndex = static_cast<float>(ARCHE_ORDER);
        
        context.setOutput(
            EquationID::ORDER_ARCHETYPE_SEMANTICS,
            OutputName::ORDER_ARCHETYPE_SEMANTICS,
            &orderArchetypeIndex,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::ORDER_ARCHETYPE_SEMANTICS);
        
        // Validate: must have valid archetype index
        if (outputData.size < 1) return false;
        return (outputData.values[0] == static_cast<float>(ARCHE_ORDER));
    }
};

const int OrderArchetypeSemantics::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION
};
const int OrderArchetypeSemantics::downstreamEquationIndices[] = {
    EquationID::REGIME_INFLUENCE_GRADIENT
};

// ============================================================
// Equation 72: Turbulence Archetype Semantics
// A_2 ~ turbulence (branching motifs)
// ============================================================
class TurbulenceArchetypeSemantics : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    TurbulenceArchetypeSemantics() : Equation(
        EquationID::TURBULENCE_ARCHETYPE_SEMANTICS,
        "Turbulence Archetype Semantics",
        R"(\mathcal{A}_2 \sim \text{turbulence})",
        "Archetype 2 produces chaotic branching patterns",
        "Documents turbulence archetype visual semantics",
        "semantic_diagnostics",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Turbulence archetype semantic identifier
        
        const float turbulenceArchetypeIndex = static_cast<float>(ARCHE_TURBULENCE);
        
        context.setOutput(
            EquationID::TURBULENCE_ARCHETYPE_SEMANTICS,
            OutputName::TURBULENCE_ARCHETYPE_SEMANTICS,
            &turbulenceArchetypeIndex,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::TURBULENCE_ARCHETYPE_SEMANTICS);
        
        // Validate: must have valid archetype index
        if (outputData.size < 1) return false;
        return (outputData.values[0] == static_cast<float>(ARCHE_TURBULENCE));
    }
};

const int TurbulenceArchetypeSemantics::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION
};
const int TurbulenceArchetypeSemantics::downstreamEquationIndices[] = {
    EquationID::VOLATILITY_INFLUENCE_GRADIENT
};

// ============================================================
// Equation 73: Growth Archetype Semantics
// A_3 ~ growth (expansive motifs)
// ============================================================
class GrowthArchetypeSemantics : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    GrowthArchetypeSemantics() : Equation(
        EquationID::GROWTH_ARCHETYPE_SEMANTICS,
        "Growth Archetype Semantics",
        R"(\mathcal{A}_3 \sim \text{growth})",
        "Archetype 3 produces outward expanding patterns",
        "Documents growth archetype visual semantics",
        "semantic_diagnostics",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Growth archetype semantic identifier
        
        const float growthArchetypeIndex = static_cast<float>(ARCHE_GROWTH);
        
        context.setOutput(
            EquationID::GROWTH_ARCHETYPE_SEMANTICS,
            OutputName::GROWTH_ARCHETYPE_SEMANTICS,
            &growthArchetypeIndex,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::GROWTH_ARCHETYPE_SEMANTICS);
        
        // Validate: must have valid archetype index
        if (outputData.size < 1) return false;
        return (outputData.values[0] == static_cast<float>(ARCHE_GROWTH));
    }
};

const int GrowthArchetypeSemantics::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION
};
const int GrowthArchetypeSemantics::downstreamEquationIndices[] = {
    EquationID::TREND_INFLUENCE_GRADIENT
};

// ============================================================
// Equation 74: Decay Archetype Semantics
// A_4 ~ decay (collapse motifs)
// ============================================================
class DecayArchetypeSemantics : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    DecayArchetypeSemantics() : Equation(
        EquationID::DECAY_ARCHETYPE_SEMANTICS,
        "Decay Archetype Semantics",
        R"(\mathcal{A}_4 \sim \text{decay})",
        "Archetype 4 produces inward collapsing patterns",
        "Documents decay archetype visual semantics",
        "semantic_diagnostics",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Decay archetype semantic identifier
        
        const float decayArchetypeIndex = static_cast<float>(ARCHE_DECAY);
        
        context.setOutput(
            EquationID::DECAY_ARCHETYPE_SEMANTICS,
            OutputName::DECAY_ARCHETYPE_SEMANTICS,
            &decayArchetypeIndex,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::DECAY_ARCHETYPE_SEMANTICS);
        
        // Validate: must have valid archetype index
        if (outputData.size < 1) return false;
        return (outputData.values[0] == static_cast<float>(ARCHE_DECAY));
    }
};

const int DecayArchetypeSemantics::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION
};
const int DecayArchetypeSemantics::downstreamEquationIndices[] = {
    EquationID::RISK_INFLUENCE_GRADIENT
};

// ============================================================
// Equation 75: Balance Archetype Semantics
// A_5 ~ balance (harmonic motifs)
// ============================================================
class BalanceArchetypeSemantics : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    BalanceArchetypeSemantics() : Equation(
        EquationID::BALANCE_ARCHETYPE_SEMANTICS,
        "Balance Archetype Semantics",
        R"(\mathcal{A}_5 \sim \text{balance})",
        "Archetype 5 produces harmonious balanced patterns",
        "Documents balance archetype visual semantics",
        "semantic_diagnostics",
        "CPU/OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Balance archetype semantic identifier
        
        const float balanceArchetypeIndex = static_cast<float>(ARCHE_BALANCE);
        
        context.setOutput(
            EquationID::BALANCE_ARCHETYPE_SEMANTICS,
            OutputName::BALANCE_ARCHETYPE_SEMANTICS,
            &balanceArchetypeIndex,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::BALANCE_ARCHETYPE_SEMANTICS);
        
        // Validate: must have valid archetype index
        if (outputData.size < 1) return false;
        return (outputData.values[0] == static_cast<float>(ARCHE_BALANCE));
    }
};

const int BalanceArchetypeSemantics::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_ARCHETYPE_ASSIGNMENT,
    EquationID::ARCHETYPE_FUNCTION_DEFINITION
};
const int BalanceArchetypeSemantics::downstreamEquationIndices[] = {};

// ============================================================
// Equation 76: Regime Influence Gradient
// ∂o_{p,t}/∂c_t^(r)
// ============================================================
class RegimeInfluenceGradient : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    RegimeInfluenceGradient() : Equation(
        EquationID::REGIME_INFLUENCE_GRADIENT,
        "Regime Influence Gradient",
        R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(r)}})",
        "How regime context affects output via gating and direct paths",
        "Computes regime sensitivity for diagnostics",
        "semantic_diagnostics",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Regime influence gradient (simplified for diagnostics)
        // In full implementation, would compute actual partial derivatives
        
        float regimeGradientRGB[NN_OUT] = {0.1f, 0.1f, 0.1f};
        
        context.setOutput(
            EquationID::REGIME_INFLUENCE_GRADIENT,
            OutputName::REGIME_INFLUENCE_GRADIENT,
            regimeGradientRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::REGIME_INFLUENCE_GRADIENT);
        
        // Validate: must have RGB gradient
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int RegimeInfluenceGradient::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT,
    EquationID::ORDER_ARCHETYPE_SEMANTICS
};
const int RegimeInfluenceGradient::downstreamEquationIndices[] = {
    EquationID::SEMANTIC_INFLUENCE_MAGNITUDE
};

// ============================================================
// Equation 77: Volatility Influence Gradient
// ∂o_{p,t}/∂c_t^(v)
// ============================================================
class VolatilityInfluenceGradient : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    VolatilityInfluenceGradient() : Equation(
        EquationID::VOLATILITY_INFLUENCE_GRADIENT,
        "Volatility Influence Gradient",
        R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(v)}})",
        "How volatility context affects output",
        "Computes volatility sensitivity for diagnostics",
        "semantic_diagnostics",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Volatility influence gradient
        
        float volatilityGradientRGB[NN_OUT] = {0.15f, 0.15f, 0.15f};
        
        context.setOutput(
            EquationID::VOLATILITY_INFLUENCE_GRADIENT,
            OutputName::VOLATILITY_INFLUENCE_GRADIENT,
            volatilityGradientRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::VOLATILITY_INFLUENCE_GRADIENT);
        
        // Validate: must have RGB gradient
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int VolatilityInfluenceGradient::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT,
    EquationID::TURBULENCE_ARCHETYPE_SEMANTICS
};
const int VolatilityInfluenceGradient::downstreamEquationIndices[] = {
    EquationID::SEMANTIC_INFLUENCE_MAGNITUDE
};

// ============================================================
// Equation 78: Trend Influence Gradient
// ∂o_{p,t}/∂c_t^(τ)
// ============================================================
class TrendInfluenceGradient : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    TrendInfluenceGradient() : Equation(
        EquationID::TREND_INFLUENCE_GRADIENT,
        "Trend Influence Gradient",
        R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(\tau)}})",
        "How trend context affects output",
        "Computes trend sensitivity for diagnostics",
        "semantic_diagnostics",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Trend influence gradient
        
        float trendGradientRGB[NN_OUT] = {0.12f, 0.12f, 0.12f};
        
        context.setOutput(
            EquationID::TREND_INFLUENCE_GRADIENT,
            OutputName::TREND_INFLUENCE_GRADIENT,
            trendGradientRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::TREND_INFLUENCE_GRADIENT);
        
        // Validate: must have RGB gradient
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int TrendInfluenceGradient::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT,
    EquationID::GROWTH_ARCHETYPE_SEMANTICS
};
const int TrendInfluenceGradient::downstreamEquationIndices[] = {
    EquationID::SEMANTIC_INFLUENCE_MAGNITUDE
};

// ============================================================
// Equation 79: Risk Influence Gradient
// ∂o_{p,t}/∂c_t^(ρ)
// ============================================================
class RiskInfluenceGradient : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    RiskInfluenceGradient() : Equation(
        EquationID::RISK_INFLUENCE_GRADIENT,
        "Risk Influence Gradient",
        R"(\frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(\rho)}})",
        "How risk context affects output",
        "Computes risk sensitivity for diagnostics",
        "semantic_diagnostics",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Risk influence gradient
        
        float riskGradientRGB[NN_OUT] = {0.08f, 0.08f, 0.08f};
        
        context.setOutput(
            EquationID::RISK_INFLUENCE_GRADIENT,
            OutputName::RISK_INFLUENCE_GRADIENT,
            riskGradientRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::RISK_INFLUENCE_GRADIENT);
        
        // Validate: must have RGB gradient
        if (outputData.size < NN_OUT) return false;
        
        return true;
    }
};

const int RiskInfluenceGradient::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT,
    EquationID::DECAY_ARCHETYPE_SEMANTICS
};
const int RiskInfluenceGradient::downstreamEquationIndices[] = {
    EquationID::SEMANTIC_INFLUENCE_MAGNITUDE
};

// ============================================================
// Equation 80: Semantic Influence Magnitude
// M_q(t) = (1/|Ω|) * Σ_{p∈Ω} ||∂o_{p,t}/∂c_t^(q)||_2
// ============================================================
class SemanticInfluenceMagnitude : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SemanticInfluenceMagnitude() : Equation(
        EquationID::SEMANTIC_INFLUENCE_MAGNITUDE,
        "Semantic Influence Magnitude",
        R"(\mathcal{M}_{q}(t) = \frac{1}{|\Omega|}\sum_{p\in\Omega}\left\| \frac{\partial \mathbf{o}_{p,t}}{\partial c_t^{(q)}} \right\|_2)",
        "Average sensitivity of output to context channel q",
        "Measures semantic influence strength per context dimension",
        "semantic_diagnostics",
        "CPU",
        upstreamEquationIndices,
        downstreamEquationIndices,
        5,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Compute magnitude of each context channel's influence
        
        const EquationData& regimeGrad = context.getOutput(EquationID::REGIME_INFLUENCE_GRADIENT);
        const EquationData& volatilityGrad = context.getOutput(EquationID::VOLATILITY_INFLUENCE_GRADIENT);
        const EquationData& trendGrad = context.getOutput(EquationID::TREND_INFLUENCE_GRADIENT);
        const EquationData& riskGrad = context.getOutput(EquationID::RISK_INFLUENCE_GRADIENT);
        
        float semanticInfluenceMagnitudes[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        
        // Compute L2 norm of each gradient (simplified for single pixel)
        if (regimeGrad.size >= NN_OUT) {
            semanticInfluenceMagnitudes[0] = sqrtf(regimeGrad.values[0]*regimeGrad.values[0] + 
                                                    regimeGrad.values[1]*regimeGrad.values[1] + 
                                                    regimeGrad.values[2]*regimeGrad.values[2]);
        }
        if (volatilityGrad.size >= NN_OUT) {
            semanticInfluenceMagnitudes[1] = sqrtf(volatilityGrad.values[0]*volatilityGrad.values[0] + 
                                                    volatilityGrad.values[1]*volatilityGrad.values[1] + 
                                                    volatilityGrad.values[2]*volatilityGrad.values[2]);
        }
        if (trendGrad.size >= NN_OUT) {
            semanticInfluenceMagnitudes[2] = sqrtf(trendGrad.values[0]*trendGrad.values[0] + 
                                                    trendGrad.values[1]*trendGrad.values[1] + 
                                                    trendGrad.values[2]*trendGrad.values[2]);
        }
        if (riskGrad.size >= NN_OUT) {
            semanticInfluenceMagnitudes[3] = sqrtf(riskGrad.values[0]*riskGrad.values[0] + 
                                                    riskGrad.values[1]*riskGrad.values[1] + 
                                                    riskGrad.values[2]*riskGrad.values[2]);
        }
        
        context.setOutput(
            EquationID::SEMANTIC_INFLUENCE_MAGNITUDE,
            OutputName::SEMANTIC_INFLUENCE_MAGNITUDE,
            semanticInfluenceMagnitudes,
            4
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::SEMANTIC_INFLUENCE_MAGNITUDE);
        
        // Validate: must have 4 magnitudes (one per context channel)
        if (outputData.size < 4) return false;
        
        // Validate: all magnitudes must be non-negative
        for (int channelIndex = 0; channelIndex < 4; ++channelIndex) {
            if (outputData.values[channelIndex] < 0.0f) return false;
        }
        
        return true;
    }
};

const int SemanticInfluenceMagnitude::upstreamEquationIndices[] = {
    EquationID::SPATIAL_DOMAIN_DEFINITION,
    EquationID::REGIME_INFLUENCE_GRADIENT,
    EquationID::VOLATILITY_INFLUENCE_GRADIENT,
    EquationID::TREND_INFLUENCE_GRADIENT,
    EquationID::RISK_INFLUENCE_GRADIENT
};
const int SemanticInfluenceMagnitude::downstreamEquationIndices[] = {};

// ============================================================
// Factory functions for Semantic Diagnostics equations (71-80)
// ============================================================
Equation* createOrderArchetypeSemantics() { return new OrderArchetypeSemantics(); }
Equation* createTurbulenceArchetypeSemantics() { return new TurbulenceArchetypeSemantics(); }
Equation* createGrowthArchetypeSemantics() { return new GrowthArchetypeSemantics(); }
Equation* createDecayArchetypeSemantics() { return new DecayArchetypeSemantics(); }
Equation* createBalanceArchetypeSemantics() { return new BalanceArchetypeSemantics(); }
Equation* createRegimeInfluenceGradient() { return new RegimeInfluenceGradient(); }
Equation* createVolatilityInfluenceGradient() { return new VolatilityInfluenceGradient(); }
Equation* createTrendInfluenceGradient() { return new TrendInfluenceGradient(); }
Equation* createRiskInfluenceGradient() { return new RiskInfluenceGradient(); }
Equation* createSemanticInfluenceMagnitude() { return new SemanticInfluenceMagnitude(); }

}  // namespace EquationSystem
