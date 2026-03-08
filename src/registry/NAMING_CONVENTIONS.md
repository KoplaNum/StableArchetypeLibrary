# Stable Archetype Library - Variable Naming Conventions

## Scientific Notation Standards

This document defines the proper variable naming for all 100 equations based on neural network, neural rendering, and dynamical systems conventions.

---

## Group 1: Archetype Ontology (Eq 1-12)

### Core Mathematical Objects

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathfrak{A}$ | archetypeLibrary | `archetypeLibrary` | Full library of archetype operators |
| $\mathcal{A}_k$ | archetypeOperator | `archetypeOperator[k]` | k-th archetype neural operator |
| $K$ | libraryCardinality | `libraryCardinality` | Number of archetypes in library |
| $\Theta_k$ | archetypeParameterSet | `archetypeParams[k]` | Parameter tuple for archetype k |
| $W_k^{(1)}$ | firstLayerWeights | `firstLayerWeights[k]` | Layer 1 weight matrix for archetype k |
| $b_k^{(1)}$ | firstLayerBiases | `firstLayerBiases[k]` | Layer 1 bias vector for archetype k |
| $W_k^{(2)}$ | secondLayerWeights | `secondLayerWeights[k]` | Layer 2 weight matrix for archetype k |
| $b_k^{(2)}$ | secondLayerBiases | `secondLayerBiases[k]` | Layer 2 bias vector for archetype k |
| $\Theta$ | globalParameterLibrary | `globalParamLibrary` | Union of all archetype parameters |

### Dimensional Constants

| Symbol | C++ Name | Value | Description |
|--------|----------|-------|-------------|
| $d_s$ | `spatialDim` | 2 | Spatial input dimension |
| $d_c$ | `contextDim` | 4 | Context input dimension |
| $d_o$ | `outputDim` | 3 | Output color dimension |
| $d_h$ | `hiddenDim` | 16 | Hidden layer width |

---

## Group 2: Context Dynamics (Eq 21-30)

### Context Vector Components

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathbf{c}_t$ | semanticContextVector | `contextVector` | 4D semantic context at time t |
| $c_t^{(r)}$ | regimeState | `regimeState` | Regime component of context |
| $c_t^{(v)}$ | volatilityState | `volatilityState` | Volatility component of context |
| $c_t^{(\tau)}$ | trendState | `trendState` | Trend component of context |
| $c_t^{(\rho)}$ | riskState | `riskState` | Risk component of context |

### Dynamical Parameters

| Symbol | C++ Name | Description |
|--------|----------|-------------|
| $a_r, b_r$ | `regimeAmp1`, `regimeAmp2` | Regime oscillation amplitudes |
| $\omega_r, \nu_r$ | `regimeFreq1`, `regimeFreq2` | Regime oscillation frequencies |
| $\eta_t^{(q)}$ | `signedNoise[q]` | Signed stochastic excitation |
| $u_t^{(q)}$ | `unitRandom[q]` | Unit-interval random driver |
| $\bar{w}_{1,t}$ | `firstLayerMeanWeight` | Mean of first layer weights |
| $\bar{w}_{2,t}$ | `secondLayerMeanWeight` | Mean of second layer weights |
| $\bar{m}_t$ | `globalWeightMagnitude` | Global parameter magnitude statistic |

---

## Group 3: Spatial Geometry (Eq 13-20)

### Spatial Coordinates

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\Omega$ | spatialDomain | `spatialDomain` | 2D pixel grid domain |
| $(i, j)$ | pixelCoords | `pixelCoords` | Integer pixel coordinates |
| $(x_p, y_p)$ | normalizedCoords | `normalizedCoords` | Normalized coordinates in [-1, 1] |
| $r_p$ | radialDistance | `radialDistance` | Radial distance from center |
| $\vartheta_p$ | polarAngle | `polarAngle` | Angular position (atan2) |
| $v_p$ | vignetteFactor | `vignetteFactor` | Radial falloff multiplier |
| $\mathbf{g}_p$ | geometricFeatureVector | `geometricFeatures` | Complete geometric descriptor |

---

## Group 4: Pixel Input Synthesis (Eq 31-40)

### Input Vector Components

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathbf{z}_{p,t}$ | pixelInputVector | `pixelInputVector` | 6D input vector per pixel |
| $\tilde{c}_{p,t}^{(r)}$ | modulatedRegime | `modulatedRegime` | Regime with pixel noise |
| $\tilde{c}_{p,t}^{(v)}$ | modulatedVolatility | `modulatedVolatility` | Volatility with pixel noise |
| $\tilde{c}_{p,t}^{(\tau)}$ | modulatedTrend | `modulatedTrend` | Trend with spatial modulation |
| $\tilde{c}_{p,t}^{(\rho)}$ | modulatedRisk | `modulatedRisk` | Risk with spatial modulation |
| $\xi_{p,t}$ | pixelSignedNoise | `pixelSignedNoise` | Per-pixel signed noise |
| $\chi_{p,t}$ | pixelUnitHash | `pixelUnitHash` | Per-pixel unit hash output |
| $m_{p,t}$ | pixelHashInteger | `pixelHashInteger` | Mixed hash integer |

---

## Group 5: Neural Evaluation (Eq 41-50)

### MLP Computation Variables

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathbf{h}_{k,p,t}^{(1)}$ | firstLayerPreactivation | `firstLayerPreactivation[k]` | Layer 1 pre-activation |
| $\mathbf{a}_{k,p,t}^{(1)}$ | firstLayerActivation | `firstLayerActivation[k]` | Layer 1 activation (tanh) |
| $\mathbf{h}_{k,p,t}^{(2)}$ | secondLayerPreactivation | `secondLayerPreactivation[k]` | Layer 2 pre-activation |
| $\mathbf{o}_{k,p,t}$ | archetypeOutput | `archetypeOutput[k]` | Archetype color output |
| $\Phi_k$ | archetypeNeuralMap | `archetypeNeuralMap[k]` | Archetype neural operator |
| $o_{k,p,t}^{(R)}$ | archetypeOutputRed | `archetypeOutputRed[k]` | Red channel output |
| $o_{k,p,t}^{(G)}$ | archetypeOutputGreen | `archetypeOutputGreen[k]` | Green channel output |
| $o_{k,p,t}^{(B)}$ | archetypeOutputBlue | `archetypeOutputBlue[k]` | Blue channel output |

---

## Group 6: Controller/Gating (Eq 51-60)

### Controller Variables

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathbf{q}_t$ | controllerLogits | `controllerLogits` | Raw archetype scores |
| $q_{k,t}$ | archetypeLogit | `archetypeLogit[k]` | Logit for archetype k |
| $\boldsymbol{\pi}(t)$ | archetypeWeights | `archetypeWeights` | Softmax archetype weights |
| $\pi_k(t)$ | archetypeWeight | `archetypeWeight[k]` | Weight for archetype k |
| $\tau_t$ | softmaxTemperature | `softmaxTemperature` | Temperature parameter |
| $k_t^\star$ | selectedArchetype | `selectedArchetype` | Dominant archetype index |
| $H_\pi(t)$ | gatingEntropy | `gatingEntropy` | Shannon entropy of weights |
| $\operatorname{conf}(t)$ | gatingConfidence | `gatingConfidence` | Selection confidence |
| $\Delta_\pi(t)$ | gatingTemporalDiff | `gatingTemporalDiff` | L1 change in weights |

---

## Group 7: Blending (Eq 61-70)

### Blending Variables

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $\mathbf{o}_{p,t}$ | blendedOutput | `blendedOutput` | Weighted sum of archetype outputs |
| $o_{p,t}^{(c)}$ | blendedChannel | `blendedChannel[c]` | Blended color channel c |
| $\lambda_t$ | mixingLambda | `mixingLambda` | Hard/soft mixing parameter |
| $\bar{\mathbf{o}}_t$ | frameMeanOutput | `frameMeanOutput` | Frame average color |
| $\operatorname{Var}_t(\mathbf{o})$ | outputVariance | `outputVariance` | Spatial variance of output |

---

## Group 8: Color Synthesis (Eq 91-100)

### Final Color Variables

| Symbol | Scientific Name | C++ Variable Name | Description |
|--------|----------------|-------------------|-------------|
| $s_{p,t}$ | stripePattern | `stripePattern` | Diagonal stripe modulation |
| $R_{p,t}$ | redChannel | `redChannel` | Final red output |
| $G_{p,t}$ | greenChannel | `greenChannel` | Final green output |
| $B_{p,t}$ | blueChannel | `blueChannel` | Final blue output |
| $\mathbf{I}_{p,t}$ | finalColorVector | `finalColorVector` | Complete RGB color |
| $\mathbf{I}_{p,t}^{(8)}$ | quantizedColor | `quantizedColor` | 8-bit color values |
| $\mathbf{I}_{p,t}^{\text{PBO}}$ | pboColorBuffer | `pboColorBuffer` | PBO texture data |

---

## Naming Rules for C++ Implementation

### 1. Variable Names
- Use **camelCase** for local variables
- Use **PascalCase** for class names and types
- Use **UPPER_CASE** for constants
- Prefix with subsystem for clarity: `context_`, `spatial_`, `neural_`, etc.

### 2. Array/Buffer Names
- Plural for arrays: `archetypeWeights`, `controllerLogits`
- Include dimension in comment: `// [K_ARCHETYPES]`
- Use indexed access: `archetypeWeights[k]`

### 3. Mathematical Operations
- `compute` for calculations: `computeRadialDistance()`
- `apply` for transformations: `applyTanhActivation()`
- `normalize` for scaling: `normalizeCoordinates()`
- `blend` for mixing: `blendArchetypeOutputs()`
- `modulate` for context influence: `modulateRegimeInput()`

### 4. Validation Functions
- `validate` prefix: `validateOutputBounds()`
- `check` prefix: `checkDependencySatisfied()`
- Return `bool` for pass/fail

### 5. Output Storage
- Use `setOutput(equationNum, name, values, count)` pattern
- Name outputs after the mathematical object: `"context_vector"`, `"archetype_weights"`

---

## Example Implementation Pattern

```cpp
bool Equation022::evaluate(EquationContext& ctx) {
    // Eq 22: Regime-state dynamics
    // c_t^{(r)} = tanh(a_r*sin(ω_r*t) + b_r*cos(ν_r*t) + η_t^{(r)})
    
    // Get inputs from upstream equations
    const float phase = ctx.getPhase();
    const float signedNoise = ctx.getSignedNoise(REGIME_CHANNEL);
    
    // Compute regime dynamics with dual-frequency oscillation
    const float regimeAmp1 = 0.9f;
    const float regimeFreq1 = 0.31f;
    const float regimeAmp2 = 0.6f;
    const float regimeFreq2 = 0.17f;
    const float noiseAmp = 0.35f;
    
    const float oscillation = regimeAmp1 * sinf(regimeFreq1 * phase) 
                            + regimeAmp2 * cosf(regimeFreq2 * phase);
    const float regimeState = tanhf(oscillation + noiseAmp * signedNoise);
    
    // Store output with scientific name
    ctx.setOutput(22, "regime_state", &regimeState, 1);
    
    // Update context vector for downstream equations
    ContextVector context = ctx.getContextVector();
    context.regimeState = regimeState;
    ctx.setContextVector(context);
    
    return true;
}

bool Equation022::validate(const EquationContext& ctx) const {
    const EquationData& output = ctx.getOutput(22);
    
    // Regime must be in [-1, 1] (tanh output range)
    if (output.size < 1) return false;
    if (output.values[0] < -1.0f || output.values[0] > 1.0f) return false;
    
    return true;
}
```
