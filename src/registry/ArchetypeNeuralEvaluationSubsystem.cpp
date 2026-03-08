// ArchetypeNeuralEvaluation.cpp - Neural Network Evaluation Layer
#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>
namespace EquationSystem {
class FirstLayerPreactivation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    FirstLayerPreactivation() : Equation(EquationID::FIRST_LAYER_PREACTIVATION, "First Layer Preactivation", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 6, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&input=ctx.getOutput(EquationID::PIXEL_INPUT_VECTOR); if(input.size<NN_IN)return false; const float*W1=ctx.getFirstLayerWeights(0);const float*b1=ctx.getFirstLayerBiases(0); if(!W1||!b1)return false; float h[NN_H]; for(int j=0;j<NN_H;++j){float acc=b1[j];for(int i=0;i<NN_IN;++i)acc+=input.values[i]*W1[j*NN_IN+i];h[j]=acc;} ctx.setOutput(EquationID::FIRST_LAYER_PREACTIVATION, OutputName::H1_PREACT, h, NN_H); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::FIRST_LAYER_PREACTIVATION).size>=NN_H; }
};
const int FirstLayerPreactivation::upstreamEquationIndices[]={EquationID::ARCHETYPE_PARAMETERIZATION,EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,EquationID::SPATIAL_INPUT_DIMENSION,EquationID::CONTEXT_INPUT_DIMENSION,EquationID::HIDDEN_LAYER_WIDTH,EquationID::PIXEL_INPUT_VECTOR};
const int FirstLayerPreactivation::downstreamEquationIndices[]={EquationID::FIRST_LAYER_ACTIVATION};
class FirstLayerActivation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    FirstLayerActivation() : Equation(EquationID::FIRST_LAYER_ACTIVATION, "First Layer Activation", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&pre=ctx.getOutput(EquationID::FIRST_LAYER_PREACTIVATION); if(pre.size<NN_H)return false; float a[NN_H];for(int i=0;i<NN_H;++i)a[i]=tanhf(pre.values[i]); ctx.setOutput(EquationID::FIRST_LAYER_ACTIVATION, OutputName::H1_ACT, a, NN_H); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::FIRST_LAYER_ACTIVATION); if(o.size<NN_H)return false; for(int i=0;i<NN_H;++i)if(o.values[i]<-1.0f||o.values[i]>1.0f)return false; return true; }
};
const int FirstLayerActivation::upstreamEquationIndices[]={EquationID::HIDDEN_LAYER_WIDTH,EquationID::FIRST_LAYER_PREACTIVATION};
const int FirstLayerActivation::downstreamEquationIndices[]={EquationID::SECOND_LAYER_PREACTIVATION};
class SecondLayerPreactivation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    SecondLayerPreactivation() : Equation(EquationID::SECOND_LAYER_PREACTIVATION, "Second Layer Preactivation", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 5, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&a=ctx.getOutput(EquationID::FIRST_LAYER_ACTIVATION); if(a.size<NN_H)return false; const float*W2=ctx.getSecondLayerWeights(0);const float*b2=ctx.getSecondLayerBiases(0); if(!W2||!b2)return false; float h2[NN_OUT];for(int k=0;k<NN_OUT;++k){float acc=b2[k];for(int j=0;j<NN_H;++j)acc+=a.values[j]*W2[k*NN_H+j];h2[k]=acc;} ctx.setOutput(EquationID::SECOND_LAYER_PREACTIVATION, OutputName::H2_PREACT, h2, NN_OUT); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::SECOND_LAYER_PREACTIVATION).size>=NN_OUT; }
};
const int SecondLayerPreactivation::upstreamEquationIndices[]={EquationID::ARCHETYPE_PARAMETERIZATION,EquationID::GLOBAL_ARCHETYPE_PARAMETER_LIBRARY,EquationID::OUTPUT_COLOR_DIMENSION,EquationID::HIDDEN_LAYER_WIDTH,EquationID::FIRST_LAYER_ACTIVATION};
const int SecondLayerPreactivation::downstreamEquationIndices[]={EquationID::OUTPUT_ACTIVATION};
class OutputActivation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    OutputActivation() : Equation(EquationID::OUTPUT_ACTIVATION, "Output Activation", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 5) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&h2=ctx.getOutput(EquationID::SECOND_LAYER_PREACTIVATION); if(h2.size<NN_OUT)return false; float o[NN_OUT];for(int k=0;k<NN_OUT;++k){float s=0.5f+0.5f*tanhf(h2.values[k]);o[k]=(s<0.0f)?0.0f:((s>1.0f)?1.0f:s);} ctx.setOutput(EquationID::OUTPUT_ACTIVATION, OutputName::OUTPUT_ACT, o, NN_OUT); return true; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::OUTPUT_ACTIVATION); if(o.size<NN_OUT)return false; for(int i=0;i<NN_OUT;++i)if(o.values[i]<0.0f||o.values[i]>1.0f)return false; return true; }
};
const int OutputActivation::upstreamEquationIndices[]={EquationID::OUTPUT_COLOR_DIMENSION,EquationID::SECOND_LAYER_PREACTIVATION};
const int OutputActivation::downstreamEquationIndices[]={EquationID::OUTPUT_COLOR_COMPONENTS,EquationID::OUTPUT_BOUNDS_VALIDATION,EquationID::BLENDED_OUTPUT,EquationID::PER_CHANNEL_BLENDING,EquationID::HARD_VS_SOFT_SELECTION};
class OutputColorComponents : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    OutputColorComponents() : Equation(EquationID::OUTPUT_COLOR_COMPONENTS, "Output Color Components", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 1) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&o=ctx.getOutput(EquationID::OUTPUT_ACTIVATION); if(o.size<NN_OUT)return false; float rgb[NN_OUT];for(int i=0;i<NN_OUT;++i)rgb[i]=o.values[i]; ctx.setOutput(EquationID::OUTPUT_COLOR_COMPONENTS, OutputName::RGB_COMP, rgb, NN_OUT); return true; }
    bool validate(const EquationContext& ctx) const override { return ctx.getOutput(EquationID::OUTPUT_COLOR_COMPONENTS).size>=NN_OUT; }
};
const int OutputColorComponents::upstreamEquationIndices[]={EquationID::OUTPUT_COLOR_DIMENSION,EquationID::OUTPUT_ACTIVATION};
const int OutputColorComponents::downstreamEquationIndices[]={EquationID::PER_CHANNEL_BLENDING};
class OutputBoundsValidation : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    OutputBoundsValidation() : Equation(EquationID::OUTPUT_BOUNDS_VALIDATION, "Output Bounds Validation", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 2, 0) {}
    bool evaluate(EquationContext& ctx) override { const EquationData&o=ctx.getOutput(EquationID::OUTPUT_ACTIVATION); float v=1.0f;if(o.size>=NN_OUT){for(int i=0;i<NN_OUT;++i)if(o.values[i]<0.0f||o.values[i]>1.0f){v=0.0f;break;}}else v=0.0f; ctx.setOutput(EquationID::OUTPUT_BOUNDS_VALIDATION, OutputName::OUTPUT_BOUNDS, &v, 1); return v==1.0f; }
    bool validate(const EquationContext& ctx) const override { const EquationData&o=ctx.getOutput(EquationID::OUTPUT_BOUNDS_VALIDATION); return o.size>=1&&o.values[0]==1.0f; }
};
const int OutputBoundsValidation::upstreamEquationIndices[]={EquationID::OUTPUT_COLOR_DIMENSION,EquationID::OUTPUT_ACTIVATION};
const int OutputBoundsValidation::downstreamEquationIndices[]={};
class ArchetypeFunctionDefinition : public Equation {
private: static const int upstreamEquationIndices[]; static const int downstreamEquationIndices[];
public:
    ArchetypeFunctionDefinition() : Equation(EquationID::ARCHETYPE_FUNCTION_DEFINITION, "Archetype Function Definition", "", "", "", "archetype_neural_evaluation", "OpenCL", upstreamEquationIndices, downstreamEquationIndices, 3, 3) {}
    bool evaluate(Equ
