// ControllerGating.cpp - Softmax Gating & Archetype Selection
#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>
namespace EquationSystem {
class ControllerLogits : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ControllerLogits() : Equation(EquationID::CONTROLLER_LOGITS, "Controller Logits", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 3, 2) {}
    bool evaluate(EquationContext& ctx) override { float q[K_ARCHETYPES]; q[ARCHE_ORDER]=0.5f*ctx.getRegimeState()+0.3f*ctx.getTrendState(); q[ARCHE_TURBULENCE]=0.8f*ctx.getVolatilityState()-0.2f*ctx.getRegimeState(); q[ARCHE_GROWTH]=0.6f*ctx.getTrendState()+0.4f*ctx.getRegimeState(); q[ARCHE_DECAY]=-0.6f*ctx.getTrendState()-0.3f*ctx.getVolatilityState(); q[ARCHE_BALANCE]=0.3f*ctx.getRiskState()+0.2f*(ctx.getRegimeState()+ctx.getTrendState()); ctx.setOutput(EquationID::CONTROLLER_LOGITS, OutputName::LOGITS, q, K_ARCHETYPES); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::CONTROLLER_LOGITS).size>=K_ARCHETYPES; }
};
const int ControllerLogits::upstreamEquationIndices[]={EquationID::ARCHETYPE_LIBRARY_CARDINALITY,EquationID::CONTEXT_INPUT_DIMENSION,EquationID::SEMANTIC_CONTEXT_VECTOR};
const int ControllerLogits::downstreamEquationIndices[]={EquationID::PER_ARCHETYPE_LOGIT,EquationID::SOFTMAX_GATING};
class PerArchetypeLogit : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    PerArchetypeLogit() : Equation(EquationID::PER_ARCHETYPE_LOGIT, "Per Archetype Logit", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&q=ctx.getOutput(EquationID::CONTROLLER_LOGITS); if(q.size<K_ARCHETYPES)return false; ctx.setOutput(EquationID::PER_ARCHETYPE_LOGIT, OutputName::LOGIT_K, q.values, K_ARCHETYPES); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::PER_ARCHETYPE_LOGIT).size>=K_ARCHETYPES; }
};
const int PerArchetypeLogit::upstreamEquationIndices[]={EquationID::SEMANTIC_CONTEXT_VECTOR,EquationID::CONTROLLER_LOGITS};
const int PerArchetypeLogit::downstreamEquationIndices[]={EquationID::SOFTMAX_GATING};
class SoftmaxGating : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    SoftmaxGating() : Equation(EquationID::SOFTMAX_GATING, "Softmax Gating", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 3, 8) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&q=ctx.getOutput(EquationID::CONTROLLER_LOGITS); if(q.size<K_ARCHETYPES)return false; float tau=0.5f+1.5f/(1.0f+expf(-3.0f*ctx.getVolatilityState())); float maxLogit=q.values[0]; for(int k=1;k<K_ARCHETYPES;++k)if(q.values[k]>maxLogit)maxLogit=q.values[k]; float pi[K_ARCHETYPES],sumExp=0.0f; for(int k=0;k<K_ARCHETYPES;++k){pi[k]=expf((q.values[k]-maxLogit)/tau);sumExp+=pi[k];} for(int k=0;k<K_ARCHETYPES;++k)pi[k]/=sumExp; ctx.setOutput(EquationID::SOFTMAX_GATING, OutputName::SOFTMAX, pi, K_ARCHETYPES); ctx.setArchetypeWeights(pi); int sel=0; for(int k=1;k<K_ARCHETYPES;++k)if(pi[k]>pi[sel])sel=k; ctx.setSelectedArchetypeIndex(sel); ctx.setSoftmaxTemperature(tau); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::SOFTMAX_GATING); if(o.size<K_ARCHETYPES)return false; float sum=0.0f; for(int k=0;k<K_ARCHETYPES;++k){if(o.values[k]<0.0f||o.values[k]>1.0f)return false;sum+=o.values[k];} return (sum>0.999f&&sum<1.001f); }
};
const int SoftmaxGating::upstreamEquationIndices[]={EquationID::ARCHETYPE_LIBRARY_CARDINALITY,EquationID::PER_ARCHETYPE_LOGIT,EquationID::TEMPERATURE_MODULATION};
const int SoftmaxGating::downstreamEquationIndices[]={EquationID::PROBABILITY_NORMALIZATION,EquationID::PROBABILITY_NON_NEGATIVITY,EquationID::DOMINANT_ARCHETYPE_SELECTION,EquationID::GATING_ENTROPY,EquationID::GATING_CONFIDENCE,EquationID::BLENDED_OUTPUT,EquationID::PER_CHANNEL_BLENDING,EquationID::HARD_VS_SOFT_SELECTION};
class ProbabilityNormalization : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ProbabilityNormalization() : Equation(EquationID::PROBABILITY_NORMALIZATION, "Probability Normalization", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 2, 0) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&w=ctx.getOutput(EquationID::SOFTMAX_GATING); float sum=0.0f;if(w.size>=K_ARCHETYPES)for(int k=0;k<K_ARCHETYPES;++k)sum+=w.values[k]; float v=(sum>0.999f&&sum<1.001f)?1.0f:0.0f; ctx.setOutput(EquationID::PROBABILITY_NORMALIZATION, OutputName::PROB_NORM, &v, 1); return v==1.0f; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::PROBABILITY_NORMALIZATION); return o.size>=1&&o.values[0]==1.0f; }
};
const int ProbabilityNormalization::upstreamEquationIndices[]={EquationID::ARCHETYPE_LIBRARY_CARDINALITY,EquationID::SOFTMAX_GATING};
const int ProbabilityNormalization::downstreamEquationIndices[]={};
class ProbabilityNonNegativity : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ProbabilityNonNegativity() : Equation(EquationID::PROBABILITY_NON_NEGATIVITY, "Probability Non-Negativity", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 2, 0) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&w=ctx.getOutput(EquationID::SOFTMAX_GATING); float v=1.0f;if(w.size>=K_ARCHETYPES)for(int k=0;k<K_ARCHETYPES;++k)if(w.values[k]<0.0f)v=0.0f; ctx.setOutput(EquationID::PROBABILITY_NON_NEGATIVITY, OutputName::PROB_NONNEG, &v, 1); return v==1.0f; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::PROBABILITY_NON_NEGATIVITY); return o.size>=1&&o.values[0]==1.0f; }
};
const int ProbabilityNonNegativity::upstreamEquationIndices[]={EquationID::ARCHETYPE_LIBRARY_CARDINALITY,EquationID::SOFTMAX_GATING};
const int ProbabilityNonNegativity::downstreamEquationIndices[]={};
class TemperatureModulation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    TemperatureModulation() : Equation(EquationID::TEMPERATURE_MODULATION, "Temperature Modulation", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 1, 1) {}
    bool evaluate(EquationContext& ctx) override { float tau=0.5f+1.5f/(1.0f+expf(-3.0f*ctx.getVolatilityState())); ctx.setOutput(EquationID::TEMPERATURE_MODULATION, OutputName::TEMPERATURE, &tau, 1); ctx.setSoftmaxTemperature(tau); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::TEMPERATURE_MODULATION); return o.size>=1&&o.values[0]>=0.5f&&o.values[0]<=2.0f; }
};
const int TemperatureModulation::upstreamEquationIndices[]={EquationID::VOLATILITY_STATE_DYNAMICS};
const int TemperatureModulation::downstreamEquationIndices[]={EquationID::SOFTMAX_GATING};
class DominantArchetypeSelection : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    DominantArchetypeSelection() : Equation(EquationID::DOMINANT_ARCHETYPE_SELECTION, "Dominant Archetype Selection", "", "", "", "controller_gating", "CPU", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&w=ctx.getOutput(EquationID::SOFTMAX_GATING); if(w.size<K_ARCHETYPES)return false; int sel=0;for(int k=1
