// Equation021_030_ContextEvolution.cpp - Context Evolution-30)
#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>
namespace EquationSystem {
class SemanticContextVector : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    SemanticContextVector() : Equation(EquationID::SEMANTIC_CONTEXT_VECTOR, "Semantic Context Vector", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 1, 6) {}
    bool evaluate(EquationContext& ctx) override { const float d[4]={ctx.getRegimeState(),ctx.getVolatilityState(),ctx.getTrendState(),ctx.getRiskState()}; ctx.setOutput(EquationID::SEMANTIC_CONTEXT_VECTOR, OutputName::CONTEXT_VEC, d, 4); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData& o=ctx.getOutput(EquationID::SEMANTIC_CONTEXT_VECTOR); if(o.size<4)return false; for(int i=0;i<4;++i)if(o.values[i]<-1.0f||o.values[i]>1.0f)return false; return true; }
};
const int SemanticContextVector::upstreamEquationIndices[]={EquationID::CONTEXT_INPUT_DIMENSION};
const int SemanticContextVector::downstreamEquationIndices[]={EquationID::REGIME_STATE_DYNAMICS,EquationID::VOLATILITY_STATE_DYNAMICS,EquationID::TREND_STATE_DYNAMICS,EquationID::RISK_STATE_DYNAMICS,EquationID::CONTROLLER_LOGITS,EquationID::PER_ARCHETYPE_LOGIT};
class RegimeStateDynamics : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    RegimeStateDynamics() : Equation(EquationID::REGIME_STATE_DYNAMICS, "Regime State Dynamics", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 2, 2) {}
    bool evaluate(EquationContext& ctx) override { const float v=tanhf(0.9f*sinf(0.31f*ctx.getPhase())+0.6f*cosf(0.17f*ctx.getPhase())+0.35f*ctx.getRegimeState()); ctx.setOutput(EquationID::REGIME_STATE_DYNAMICS, OutputName::REGIME, &v, 1); ctx.setContext(v,ctx.getVolatilityState(),ctx.getTrendState(),ctx.getRiskState()); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData& o=ctx.getOutput(EquationID::REGIME_STATE_DYNAMICS); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int RegimeStateDynamics::upstreamEquationIndices[]={EquationID::SEMANTIC_CONTEXT_VECTOR,EquationID::SIGNED_STOCHASTIC_EXCITATION};
const int RegimeStateDynamics::downstreamEquationIndices[]={EquationID::RISK_STATE_DYNAMICS,EquationID::MODULATED_REGIME_INPUT};
class VolatilityStateDynamics : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    VolatilityStateDynamics() : Equation(EquationID::VOLATILITY_STATE_DYNAMICS, "Volatility State Dynamics", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 3, 3) {}
    bool evaluate(EquationContext& ctx) override { float v=0.5f+0.24f; if(v<-1.0f)v=-1.0f; if(v>1.0f)v=1.0f; ctx.setOutput(EquationID::VOLATILITY_STATE_DYNAMICS, OutputName::VOLATILITY, &v, 1); ctx.setContext(ctx.getRegimeState(),v,ctx.getTrendState(),ctx.getRiskState()); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData& o=ctx.getOutput(EquationID::VOLATILITY_STATE_DYNAMICS); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int VolatilityStateDynamics::upstreamEquationIndices[]={EquationID::SEMANTIC_CONTEXT_VECTOR,EquationID::GLOBAL_WEIGHT_MAGNITUDE,EquationID::SIGNED_STOCHASTIC_EXCITATION};
const int VolatilityStateDynamics::downstreamEquationIndices[]={EquationID::RISK_STATE_DYNAMICS,EquationID::MODULATED_VOLATILITY_INPUT,EquationID::TEMPERATURE_MODULATION};
class TrendStateDynamics : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    TrendStateDynamics() : Equation(EquationID::TREND_STATE_DYNAMICS, "Trend State Dynamics", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 4, 2) {}
    bool evaluate(EquationContext& ctx) override { const float v=tanhf(0.07f+0.5f*sinf(0.12f*ctx.getPhase()+1.3f)); ctx.setOutput(EquationID::TREND_STATE_DYNAMICS, OutputName::TREND, &v, 1); ctx.setContext(ctx.getRegimeState(),ctx.getVolatilityState(),v,ctx.getRiskState()); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData& o=ctx.getOutput(EquationID::TREND_STATE_DYNAMICS); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int TrendStateDynamics::upstreamEquationIndices[]={EquationID::SEMANTIC_CONTEXT_VECTOR,EquationID::FIRST_LAYER_WEIGHT_MEAN,EquationID::SECOND_LAYER_WEIGHT_MEAN,EquationID::SIGNED_STOCHASTIC_EXCITATION};
const int TrendStateDynamics::downstreamEquationIndices[]={EquationID::RISK_STATE_DYNAMICS,EquationID::MODULATED_TREND_INPUT};
class RiskStateDynamics : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    RiskStateDynamics() : Equation(EquationID::RISK_STATE_DYNAMICS, "Risk State Dynamics", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 5, 1) {}
    bool evaluate(EquationContext& ctx) override { const float v=tanhf(0.8f*ctx.getRegimeState()-0.6f*fabsf(ctx.getVolatilityState())+0.5f*ctx.getTrendState()); ctx.setOutput(EquationID::RISK_STATE_DYNAMICS, OutputName::RISK, &v, 1); ctx.setContext(ctx.getRegimeState(),ctx.getVolatilityState(),ctx.getTrendState(),v); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData& o=ctx.getOutput(EquationID::RISK_STATE_DYNAMICS); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int RiskStateDynamics::upstreamEquationIndices[]={EquationID::SEMANTIC_CONTEXT_VECTOR,EquationID::REGIME_STATE_DYNAMICS,EquationID::VOLATILITY_STATE_DYNAMICS,EquationID::TREND_STATE_DYNAMICS,EquationID::SIGNED_STOCHASTIC_EXCITATION};
const int RiskStateDynamics::downstreamEquationIndices[]={EquationID::MODULATED_RISK_INPUT};
class FirstLayerWeightMean : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    FirstLayerWeightMean() : Equation(EquationID::FIRST_LAYER_WEIGHT_MEAN, "First Layer Weight Mean", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 1, 2) {}
    bool evaluate(EquationContext& ctx) override { float s=0.0f;int c=0; for(int k=0;k<K_ARCHETYPES;++k){const float*W1=ctx.getFirstLayerWeights(k);if(W1)for(int i=0;i<NN_H*NN_IN;++i){s+=W1[i];++c;}} const float v=(c>0)?s/(float)c:0.0f; ctx.setOutput(EquationID::FIRST_LAYER_WEIGHT_MEAN, OutputName::W1_MEAN, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::FIRST_LAYER_WEIGHT_MEAN).size>=1; }
};
const int FirstLayerWeightMean::upstreamEquationIndices[]={EquationID::ARCHETYPE_PARAMETERIZATION};
const int FirstLayerWeightMean::downstreamEquationIndices[]={EquationID::TREND_STATE_DYNAMICS,EquationID::GLOBAL_WEIGHT_MAGNITUDE};
class SecondLayerWeightMean : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    SecondLayerWeightMean() : Equation(EquationID::SECOND_LAYER_WEIGHT_MEAN, "Second Layer Weight Mean", "", "", "", "context_evolution", "CPU", upstreamEquationIndices, downstreamEquationIndices, 1, 2) {}
    bool evaluate(EquationContext& ctx) override { float s=0.0f;int c=0; for(int k=0;k<K_ARCHETYPES;++k){const float*W2=ctx.getSecondLayerWeights(k);if(W2)for(int i=0;i<NN_OUT*NN_H;++i){s+=W2[i];++c;}} const float v=(c>0)?s/(float)c:0.0f; ctx.setOutput(EquationID::SECOND_LAYER_WEIGHT_MEAN, OutputName::W2_MEAN, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::SECOND_LAYER_WEIGHT_MEAN).size>=1; }
};
const int Se
