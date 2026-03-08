// Equation031_040_PixelInputSynthesis.cpp - Pixel Input Synthesis-40)
#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include "../../include/equations/pixel_input_synthesis/IntegerMixingHash.hpp"
#include <cmath>
namespace EquationSystem {
class PixelInputVector : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    PixelInputVector() : Equation(EquationID::PIXEL_INPUT_VECTOR, "Pixel Input Vector", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 6, 3) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&x=ctx.getOutput(EquationID::NORMALIZED_X_COORDINATE);const EquationData&y=ctx.getOutput(EquationID::NORMALIZED_Y_COORDINATE);const EquationData&r=ctx.getOutput(EquationID::MODULATED_REGIME_INPUT);const EquationData&v=ctx.getOutput(EquationID::MODULATED_VOLATILITY_INPUT);const EquationData&t=ctx.getOutput(EquationID::MODULATED_TREND_INPUT);const EquationData&k=ctx.getOutput(EquationID::MODULATED_RISK_INPUT); float d[6]={x.size>=1?x.values[0]:0.0f,y.size>=1?y.values[0]:0.0f,r.size>=1?r.values[0]:0.0f,v.size>=1?v.values[0]:0.0f,t.size>=1?t.values[0]:0.0f,k.size>=1?k.values[0]:0.0f}; ctx.setOutput(EquationID::PIXEL_INPUT_VECTOR, OutputName::PIXEL_INPUT_VECTOR, d, 6); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::PIXEL_INPUT_VECTOR); if(o.size<6)return false; for(int i=0;i<6;++i)if(o.values[i]<-1.0f||o.values[i]>1.0f)return false; return true; }
};
const int PixelInputVector::upstreamEquationIndices[]={EquationID::NORMALIZED_X_COORDINATE,EquationID::NORMALIZED_Y_COORDINATE,EquationID::MODULATED_REGIME_INPUT,EquationID::MODULATED_VOLATILITY_INPUT,EquationID::MODULATED_TREND_INPUT,EquationID::MODULATED_RISK_INPUT};
const int PixelInputVector::downstreamEquationIndices[]={EquationID::INPUT_BOUNDS_VALIDATION,EquationID::INPUT_VECTOR_COMPOSITION,EquationID::FIRST_LAYER_PREACTIVATION};
class ModulatedRegimeInput : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ModulatedRegimeInput() : Equation(EquationID::MODULATED_REGIME_INPUT, "Modulated Regime Input", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { float v=ctx.getRegimeState()+0.15f*sinf(ctx.getPhase()); if(v<-1.0f)v=-1.0f;if(v>1.0f)v=1.0f; ctx.setOutput(EquationID::MODULATED_REGIME_INPUT, OutputName::MODULATED_REGIME_INPUT, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::MODULATED_REGIME_INPUT); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int ModulatedRegimeInput::upstreamEquationIndices[]={EquationID::REGIME_STATE_DYNAMICS,EquationID::SIGNED_NOISE_FROM_UNIT};
const int ModulatedRegimeInput::downstreamEquationIndices[]={EquationID::PIXEL_INPUT_VECTOR};
class ModulatedVolatilityInput : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ModulatedVolatilityInput() : Equation(EquationID::MODULATED_VOLATILITY_INPUT, "Modulated Volatility Input", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { float v=ctx.getVolatilityState()+0.25f; if(v<-1.0f)v=-1.0f;if(v>1.0f)v=1.0f; ctx.setOutput(EquationID::MODULATED_VOLATILITY_INPUT, OutputName::MODULATED_VOLATILITY_INPUT, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::MODULATED_VOLATILITY_INPUT); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int ModulatedVolatilityInput::upstreamEquationIndices[]={EquationID::VOLATILITY_STATE_DYNAMICS,EquationID::SIGNED_NOISE_FROM_UNIT};
const int ModulatedVolatilityInput::downstreamEquationIndices[]={EquationID::PIXEL_INPUT_VECTOR};
class ModulatedTrendInput : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ModulatedTrendInput() : Equation(EquationID::MODULATED_TREND_INPUT, "Modulated Trend Input", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 1, 1) {}
    bool evaluate(EquationContext& ctx) override { float v=ctx.getTrendState()+0.15f*sinf(ctx.getPhase()); if(v<-1.0f)v=-1.0f;if(v>1.0f)v=1.0f; ctx.setOutput(EquationID::MODULATED_TREND_INPUT, OutputName::MODULATED_TREND_INPUT, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::MODULATED_TREND_INPUT); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int ModulatedTrendInput::upstreamEquationIndices[]={EquationID::TREND_STATE_DYNAMICS};
const int ModulatedTrendInput::downstreamEquationIndices[]={EquationID::PIXEL_INPUT_VECTOR};
class ModulatedRiskInput : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ModulatedRiskInput() : Equation(EquationID::MODULATED_RISK_INPUT, "Modulated Risk Input", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 1, 1) {}
    bool evaluate(EquationContext& ctx) override { float v=ctx.getRiskState()+0.10f*cosf(ctx.getPhase()); if(v<-1.0f)v=-1.0f;if(v>1.0f)v=1.0f; ctx.setOutput(EquationID::MODULATED_RISK_INPUT, OutputName::MODULATED_RISK_INPUT, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::MODULATED_RISK_INPUT); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int ModulatedRiskInput::upstreamEquationIndices[]={EquationID::RISK_STATE_DYNAMICS};
const int ModulatedRiskInput::downstreamEquationIndices[]={EquationID::PIXEL_INPUT_VECTOR};
class SignedNoiseFromUnit : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    SignedNoiseFromUnit() : Equation(EquationID::SIGNED_NOISE_FROM_UNIT, "Signed Noise From Unit", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 1, 2) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&u=ctx.getOutput(EquationID::UNIT_HASH_OUTPUT); float v=(u.size>=1)?2.0f*u.values[0]-1.0f:0.0f; ctx.setOutput(EquationID::SIGNED_NOISE_FROM_UNIT, OutputName::SIGNED_NOISE, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::SIGNED_NOISE_FROM_UNIT); return o.size>=1&&o.values[0]>=-1.0f&&o.values[0]<=1.0f; }
};
const int SignedNoiseFromUnit::upstreamEquationIndices[]={EquationID::UNIT_HASH_OUTPUT};
const int SignedNoiseFromUnit::downstreamEquationIndices[]={EquationID::MODULATED_REGIME_INPUT,EquationID::MODULATED_VOLATILITY_INPUT};
class UnitHashOutput : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    UnitHashOutput() : Equation(EquationID::UNIT_HASH_OUTPUT, "Unit Hash Output", "", "", "", "pixel_input_synthesis", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 1, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&h=ctx.getOutput(EquationID::INTEGER_MIXING_HASH); float v=(h.size>=1)?(float)(*(unsigned int*)&h.values[0]&0x00FFFFFFu)/16777215.0f:0.5f; ctx.setOutput(EquationID::UNIT_HASH_OUTPUT, OutputName::UNIT_HASH_OUTPUT, &v, 1); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::UNIT_HASH_OUTPUT); return o.size>=1&&o.values[0]>=0.0f&&o.values[0]<=1.0f; }
};
const int UnitHashOutput::upstreamEquationIndices[]={EquationID::INTEGER_MIXING_HASH};
const int UnitHashOutput:
