// FinalColorSynthesisSubsystem.cpp - Final Color Synthesis & Display (Eq 91-100)
// Scientific naming based on stable_archetype_100_equations_scientific_handbook.md

#include "../../include/registry/EquationBase.hpp"
#include "../../include/registry/EquationIdentifiers.hpp"
#include <cmath>

namespace EquationSystem {

// ============================================================
// Equation 91: Stripe Modulation Pattern
// s_{p,t} = 0.5 + 0.5*sin(10*(x_p+y_p) + ω_s*t + 2*ξ_{p,t})
// ============================================================
class StripeModulationPattern : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    StripeModulationPattern() : Equation(
        EquationID::STRIPE_MODULATION_PATTERN,
        "Stripe Modulation Pattern",
        R"(s_{p,t} = \frac{1}{2} + \frac{1}{2}\sin(10(x_p+y_p) + \omega_s t + 2\xi_{p,t}))",
        "Diagonal stripe pattern with temporal and noise modulation",
        "Computes stripe factor for color synthesis",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        3,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Diagonal stripe pattern for visual texture
        
        const float phase = context.getPhase();
        
        const EquationData& xData = context.getOutput(EquationID::NORMALIZED_X_COORDINATE);
        const EquationData& yData = context.getOutput(EquationID::NORMALIZED_Y_COORDINATE);
        const EquationData& noiseData = context.getOutput(EquationID::SIGNED_NOISE_FROM_UNIT);
        
        const float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        const float y = (yData.size >= 1) ? yData.values[0] : 0.0f;
        const float noise = (noiseData.size >= 1) ? noiseData.values[0] : 0.0f;
        
        const float stripeFrequency = 10.0f;
        const float noiseAmplitude = 2.0f;
        
        const float stripePatternValue = 0.5f + 0.5f * sinf(stripeFrequency * (x + y) + phase + noiseAmplitude * noise);
        
        context.setOutput(
            EquationID::STRIPE_MODULATION_PATTERN,
            OutputName::STRIPE,
            &stripePatternValue,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::STRIPE_MODULATION_PATTERN);
        
        // Validate: stripe pattern must be in [0, 1] (sinusoidal)
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int StripeModulationPattern::upstreamEquationIndices[] = {
    EquationID::NORMALIZED_X_COORDINATE,
    EquationID::NORMALIZED_Y_COORDINATE,
    EquationID::SIGNED_NOISE_FROM_UNIT
};
const int StripeModulationPattern::downstreamEquationIndices[] = {
    EquationID::RED_CHANNEL_SYNTHESIS,
    EquationID::GREEN_CHANNEL_SYNTHESIS
};

// ============================================================
// Equation 92: Red Channel Synthesis
// R_{p,t} = clip(0.70*o_{p,t}^{(R)} + 0.30*s_{p,t}, 0, 1) * v_p
// ============================================================
class RedChannelSynthesis : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    RedChannelSynthesis() : Equation(
        EquationID::RED_CHANNEL_SYNTHESIS,
        "Red Channel Synthesis",
        R"(R_{p,t} = \operatorname{clip}(0.70\,o_{p,t}^{(R)} + 0.30\,s_{p,t}, 0, 1) v_p)",
        "Red output from blended red and stripe, scaled by vignette",
        "Computes final red channel per pixel",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Red channel synthesis from blended output and stripe modulation
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        const EquationData& stripeData = context.getOutput(EquationID::STRIPE_MODULATION_PATTERN);
        const EquationData& vignetteData = context.getOutput(EquationID::VIGNETTE_FACTOR);
        
        const float blendedRed = (blendedData.size >= 1) ? blendedData.values[0] : 0.5f;
        const float stripePattern = (stripeData.size >= 1) ? stripeData.values[0] : 0.5f;
        const float vignetteFactor = (vignetteData.size >= 1) ? vignetteData.values[0] : 1.0f;
        
        // Blend coefficients
        const float blendedWeight = 0.70f;
        const float stripeWeight = 0.30f;
        
        float redChannelValue = blendedWeight * blendedRed + stripeWeight * stripePattern;
        
        // Clamp to [0, 1]
        if (redChannelValue < 0.0f) redChannelValue = 0.0f;
        if (redChannelValue > 1.0f) redChannelValue = 1.0f;
        
        // Apply vignette
        redChannelValue *= vignetteFactor;
        
        context.setOutput(
            EquationID::RED_CHANNEL_SYNTHESIS,
            OutputName::RED,
            &redChannelValue,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::RED_CHANNEL_SYNTHESIS);
        
        // Validate: red channel must be in [0, 1]
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int RedChannelSynthesis::upstreamEquationIndices[] = {
    EquationID::VIGNETTE_FACTOR,
    EquationID::OUTPUT_COLOR_COMPONENTS,
    EquationID::BLENDED_OUTPUT,
    EquationID::STRIPE_MODULATION_PATTERN
};
const int RedChannelSynthesis::downstreamEquationIndices[] = {
    EquationID::FINAL_COLOR_VECTOR,
    EquationID::BIT8_COLOR_QUANTIZATION
};

// ============================================================
// Equation 93: Green Channel Synthesis
// G_{p,t} = clip(0.85*o_{p,t}^{(G)} + 0.15*(1-s_{p,t}), 0, 1) * v_p
// ============================================================
class GreenChannelSynthesis : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    GreenChannelSynthesis() : Equation(
        EquationID::GREEN_CHANNEL_SYNTHESIS,
        "Green Channel Synthesis",
        R"(G_{p,t} = \operatorname{clip}(0.85\,o_{p,t}^{(G)} + 0.15\,(1-s_{p,t}), 0, 1) v_p)",
        "Green output from blended green and inverse stripe",
        "Computes final green channel per pixel",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Green channel synthesis with inverse stripe modulation
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        const EquationData& stripeData = context.getOutput(EquationID::STRIPE_MODULATION_PATTERN);
        const EquationData& vignetteData = context.getOutput(EquationID::VIGNETTE_FACTOR);
        
        const float blendedGreen = (blendedData.size >= 2) ? blendedData.values[1] : 0.5f;
        const float stripePattern = (stripeData.size >= 1) ? stripeData.values[0] : 0.5f;
        const float vignetteFactor = (vignetteData.size >= 1) ? vignetteData.values[0] : 1.0f;
        
        // Blend coefficients
        const float blendedWeight = 0.85f;
        const float inverseStripeWeight = 0.15f;
        
        float greenChannelValue = blendedWeight * blendedGreen + inverseStripeWeight * (1.0f - stripePattern);
        
        // Clamp to [0, 1]
        if (greenChannelValue < 0.0f) greenChannelValue = 0.0f;
        if (greenChannelValue > 1.0f) greenChannelValue = 1.0f;
        
        // Apply vignette
        greenChannelValue *= vignetteFactor;
        
        context.setOutput(
            EquationID::GREEN_CHANNEL_SYNTHESIS,
            OutputName::GREEN,
            &greenChannelValue,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::GREEN_CHANNEL_SYNTHESIS);
        
        // Validate: green channel must be in [0, 1]
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int GreenChannelSynthesis::upstreamEquationIndices[] = {
    EquationID::VIGNETTE_FACTOR,
    EquationID::OUTPUT_COLOR_COMPONENTS,
    EquationID::BLENDED_OUTPUT,
    EquationID::STRIPE_MODULATION_PATTERN
};
const int GreenChannelSynthesis::downstreamEquationIndices[] = {
    EquationID::FINAL_COLOR_VECTOR,
    EquationID::BIT8_COLOR_QUANTIZATION
};

// ============================================================
// Equation 94: Blue Channel Synthesis
// B_{p,t} = clip(0.75*o_{p,t}^{(B)} + 0.25*(0.5+0.5*cos(8*x_p-ω_b*t)), 0, 1)
// ============================================================
class BlueChannelSynthesis : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    BlueChannelSynthesis() : Equation(
        EquationID::BLUE_CHANNEL_SYNTHESIS,
        "Blue Channel Synthesis",
        R"(B_{p,t} = \operatorname{clip}(0.75\,o_{p,t}^{(B)} + 0.25(\frac{1}{2} + \frac{1}{2}\cos(8x_p-\omega_b t)), 0, 1))",
        "Blue output from blended blue and horizontal cosine",
        "Computes final blue channel per pixel",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        3,
        2
    ) {}

    bool evaluate(EquationContext& context) override {
        // Blue channel synthesis with horizontal cosine modulation
        
        const EquationData& blendedData = context.getOutput(EquationID::BLENDED_OUTPUT);
        const EquationData& xData = context.getOutput(EquationID::NORMALIZED_X_COORDINATE);
        
        const float blendedBlue = (blendedData.size >= 3) ? blendedData.values[2] : 0.5f;
        const float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        const float phase = context.getPhase();
        
        // Blend coefficients
        const float blendedWeight = 0.75f;
        const float cosineWeight = 0.25f;
        const float cosineFrequency = 8.0f;
        
        // Horizontal cosine pattern
        const float cosinePattern = 0.5f + 0.5f * cosf(cosineFrequency * x - phase);
        
        float blueChannelValue = blendedWeight * blendedBlue + cosineWeight * cosinePattern;
        
        // Clamp to [0, 1]
        if (blueChannelValue < 0.0f) blueChannelValue = 0.0f;
        if (blueChannelValue > 1.0f) blueChannelValue = 1.0f;
        
        context.setOutput(
            EquationID::BLUE_CHANNEL_SYNTHESIS,
            OutputName::BLUE,
            &blueChannelValue,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::BLUE_CHANNEL_SYNTHESIS);
        
        // Validate: blue channel must be in [0, 1]
        if (outputData.size < 1) return false;
        if (outputData.values[0] < 0.0f || outputData.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int BlueChannelSynthesis::upstreamEquationIndices[] = {
    EquationID::NORMALIZED_X_COORDINATE,
    EquationID::OUTPUT_COLOR_COMPONENTS,
    EquationID::BLENDED_OUTPUT
};
const int BlueChannelSynthesis::downstreamEquationIndices[] = {
    EquationID::FINAL_COLOR_VECTOR,
    EquationID::BIT8_COLOR_QUANTIZATION
};

// ============================================================
// Equation 95: Final Color Vector
// I_{p,t} = [R_{p,t}, G_{p,t}, B_{p,t}]^T
// ============================================================
class FinalColorVector : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    FinalColorVector() : Equation(
        EquationID::FINAL_COLOR_VECTOR,
        "Final Color Vector",
        R"(\mathbf{I}_{p,t} = \begin{bmatrix} R_{p,t} \\ G_{p,t} \\ B_{p,t} \end{bmatrix})",
        "Complete RGB color triplet for display",
        "Packages final color channels",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        3
    ) {}

    bool evaluate(EquationContext& context) override {
        // Assemble final RGB color vector
        
        const EquationData& redData = context.getOutput(EquationID::RED_CHANNEL_SYNTHESIS);
        const EquationData& greenData = context.getOutput(EquationID::GREEN_CHANNEL_SYNTHESIS);
        const EquationData& blueData = context.getOutput(EquationID::BLUE_CHANNEL_SYNTHESIS);
        
        float finalColorRGB[NN_OUT] = {
            (redData.size >= 1) ? redData.values[0] : 0.5f,
            (greenData.size >= 1) ? greenData.values[0] : 0.5f,
            (blueData.size >= 1) ? blueData.values[0] : 0.5f
        };
        
        context.setOutput(
            EquationID::FINAL_COLOR_VECTOR,
            OutputName::COLOR_VEC,
            finalColorRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::FINAL_COLOR_VECTOR);
        
        // Validate: must have RGB components
        if (outputData.size < NN_OUT) return false;
        
        // Validate: all channels must be in [0, 1]
        for (int channelIndex = 0; channelIndex < NN_OUT; ++channelIndex) {
            if (outputData.values[channelIndex] < 0.0f || outputData.values[channelIndex] > 1.0f) {
                return false;
            }
        }
        
        return true;
    }
};

const int FinalColorVector::upstreamEquationIndices[] = {
    EquationID::OUTPUT_COLOR_DIMENSION,
    EquationID::RED_CHANNEL_SYNTHESIS,
    EquationID::GREEN_CHANNEL_SYNTHESIS,
    EquationID::BLUE_CHANNEL_SYNTHESIS
};
const int FinalColorVector::downstreamEquationIndices[] = {
    EquationID::BIT8_COLOR_QUANTIZATION,
    EquationID::PBO_TEXTURE_UPLOAD,
    EquationID::COMPLETE_RENDERER_SUMMARY
};

// ============================================================
// Equation 96: 8-Bit Color Quantization
// I_{p,t}^{(8)} = 255 * I_{p,t}
// ============================================================
class Bit8ColorQuantization : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    Bit8ColorQuantization() : Equation(
        EquationID::BIT8_COLOR_QUANTIZATION,
        "Bit 8 Color Quantization",
        R"(\mathbf{I}_{p,t}^{(8)} = 255 \cdot \mathbf{I}_{p,t})",
        "Scales [0,1] float colors to [0,255] byte range",
        "Converts float colors to 8-bit for display",
        "final_color_synthesis",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Quantize float colors to 8-bit integers
        
        const EquationData& colorData = context.getOutput(EquationID::FINAL_COLOR_VECTOR);
        
        if (colorData.size < NN_OUT) return false;
        
        float quantizedColorRGB[NN_OUT];
        
        for (int channelIndex = 0; channelIndex < NN_OUT; ++channelIndex) {
            const int quantizedValue = static_cast<int>(colorData.values[channelIndex] * 255.0f + 0.5f);
            quantizedColorRGB[channelIndex] = static_cast<float>((quantizedValue < 0) ? 0 : ((quantizedValue > 255) ? 255 : quantizedValue));
        }
        
        context.setOutput(
            EquationID::BIT8_COLOR_QUANTIZATION,
            OutputName::QUANTIZED,
            quantizedColorRGB,
            NN_OUT
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::BIT8_COLOR_QUANTIZATION);
        
        // Validate: must have RGB components
        if (outputData.size < NN_OUT) return false;
        
        // Validate: all channels must be in [0, 255]
        for (int channelIndex = 0; channelIndex < NN_OUT; ++channelIndex) {
            if (outputData.values[channelIndex] < 0.0f || outputData.values[channelIndex] > 255.0f) {
                return false;
            }
        }
        
        return true;
    }
};

const int Bit8ColorQuantization::upstreamEquationIndices[] = {
    EquationID::FINAL_COLOR_VECTOR
};
const int Bit8ColorQuantization::downstreamEquationIndices[] = {
    EquationID::PBO_TEXTURE_UPLOAD
};

// ============================================================
// Equation 97: PBO Texture Upload
// I_{p,t}^{PBO} → texture upload via CL/GL sharing
// ============================================================
class PBOTextureUpload : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    PBOTextureUpload() : Equation(
        EquationID::PBO_TEXTURE_UPLOAD,
        "PBO Texture Upload",
        R"(\mathbf{I}_{p,t}^{\text{PBO}} \xrightarrow{\text{CL/GL share}} \text{texture upload})",
        "Zero-copy transfer from OpenCL to OpenGL via PBO",
        "Documents CL/GL interop texture path",
        "final_color_synthesis",
        "OpenCL/OpenGL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // PBO texture upload flag (actual upload handled by renderer)
        
        const float textureUploadComplete = 1.0f;
        
        context.setOutput(
            EquationID::PBO_TEXTURE_UPLOAD,
            OutputName::PBO_UPLOAD,
            &textureUploadComplete,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::PBO_TEXTURE_UPLOAD);
        
        // Validate: upload flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int PBOTextureUpload::upstreamEquationIndices[] = {
    EquationID::BIT8_COLOR_QUANTIZATION
};
const int PBOTextureUpload::downstreamEquationIndices[] = {
    EquationID::TEXTURE_UPDATE
};

// ============================================================
// Equation 98: Texture Update
// texture_{t+1} = U(I_{p,t}^{PBO})
// ============================================================
class TextureUpdate : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    TextureUpdate() : Equation(
        EquationID::TEXTURE_UPDATE,
        "Texture Update",
        R"(\text{texture}_{t+1} = \mathcal{U}(\mathbf{I}_{p,t}^{\text{PBO}}))",
        "Updates OpenGL texture from PBO for next frame",
        "Documents texture upload operation",
        "final_color_synthesis",
        "OpenGL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Texture update flag (actual update handled by renderer)
        
        const float textureUpdateComplete = 1.0f;
        
        context.setOutput(
            EquationID::TEXTURE_UPDATE,
            OutputName::TEX_UPDATE,
            &textureUpdateComplete,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::TEXTURE_UPDATE);
        
        // Validate: update flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int TextureUpdate::upstreamEquationIndices[] = {
    EquationID::PBO_TEXTURE_UPLOAD
};
const int TextureUpdate::downstreamEquationIndices[] = {
    EquationID::FRAME_PRESENTATION
};

// ============================================================
// Equation 99: Frame Presentation
// frame_{t+1} = Q(texture_{t+1})
// ============================================================
class FramePresentation : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    FramePresentation() : Equation(
        EquationID::FRAME_PRESENTATION,
        "Frame Presentation",
        R"(\text{frame}_{t+1} = \mathcal{Q}(\text{texture}_{t+1}))",
        "Renders textured quad to screen",
        "Documents final display operation",
        "final_color_synthesis",
        "OpenGL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        1
    ) {}

    bool evaluate(EquationContext& context) override {
        // Frame presentation flag (actual rendering handled by OpenGL)
        
        const float framePresentationComplete = 1.0f;
        
        context.setOutput(
            EquationID::FRAME_PRESENTATION,
            OutputName::FRAME_PRESENTATION,
            &framePresentationComplete,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::FRAME_PRESENTATION);
        
        // Validate: presentation flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int FramePresentation::upstreamEquationIndices[] = {
    EquationID::TEXTURE_UPDATE
};
const int FramePresentation::downstreamEquationIndices[] = {
    EquationID::COMPLETE_RENDERER_SUMMARY
};

// ============================================================
// Equation 100: Complete Renderer Summary
// I_{p,t} = Ψ(p, c_t, π(t), {Θ_k}_{k=1}^K)
// ============================================================
class CompleteRendererSummary : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    CompleteRendererSummary() : Equation(
        EquationID::COMPLETE_RENDERER_SUMMARY,
        "Complete Renderer Summary",
        R"(\boxed{\mathbf{I}_{p,t} = \Psi(p,\mathbf{c}_t,\boldsymbol{\pi}(t),\{\Theta_k\}_{k=1}^{K}))",
        "Full renderer as context-conditioned archetype-blended neural field",
        "Summarizes entire rendering pipeline",
        "final_color_synthesis",
        "CPU/OpenCL/OpenGL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        0
    ) {}

    bool evaluate(EquationContext& context) override {
        // Complete renderer summary flag
        
        const float rendererComplete = 1.0f;
        
        context.setOutput(
            EquationID::COMPLETE_RENDERER_SUMMARY,
            OutputName::RENDERER,
            &rendererComplete,
            1
        );
        
        return true;
    }

    bool validate(const EquationContext& context) const override {
        const EquationData& outputData = context.getOutput(EquationID::COMPLETE_RENDERER_SUMMARY);
        
        // Validate: renderer flag must be set
        if (outputData.size < 1) return false;
        return (outputData.values[0] == 1.0f);
    }
};

const int CompleteRendererSummary::upstreamEquationIndices[] = {
    EquationID::SEMANTIC_CONTEXT_VECTOR,
    EquationID::SOFTMAX_GATING,
    EquationID::BLENDED_OUTPUT,
    EquationID::FINAL_COLOR_VECTOR
};
const int CompleteRendererSummary::downstreamEquationIndices[] = {};

// ============================================================
// Factory functions for Final Color Synthesis equations (91-100)
// ============================================================
Equation* createStripeModulationPattern() { return new StripeModulationPattern(); }
Equation* createRedChannelSynthesis() { return new RedChannelSynthesis(); }
Equation* createGreenChannelSynthesis() { return new GreenChannelSynthesis(); }
Equation* createBlueChannelSynthesis() { return new BlueChannelSynthesis(); }
Equation* createFinalColorVector() { return new FinalColorVector(); }
Equation* createBit8ColorQuantization() { return new Bit8ColorQuantization(); }
Equation* createPBOTextureUpload() { return new PBOTextureUpload(); }
Equation* createTextureUpdate() { return new TextureUpdate(); }
Equation* createFramePresentation() { return new FramePresentation(); }
Equation* createCompleteRendererSummary() { return new CompleteRendererSummary(); }

}  // namespace EquationSystem
