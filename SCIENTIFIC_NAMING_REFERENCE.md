# Stable Archetype Library - Scientific Naming Reference

## Overview
All classes, methods, variables, and functions have been renamed to meaningful scientific names based on:
- `stable_archetype_100_equations_scientific_handbook.md`
- `stable_archetype_100_equations_deep_handbook.md`

---

## Class Naming Convention

### Format: `[Subsystem][ScientificConcept]`

**Examples:**
- `StableArchetypeLibrary` (Eq 1)
- `ArchetypeLibraryCardinality` (Eq 2)
- `SpatialDomainDefinition` (Eq 13)
- `SemanticContextVector` (Eq 21)
- `FirstLayerPreactivation` (Eq 41)
- `SoftmaxGating` (Eq 53)

---

## Variable Naming Convention

### Format: `descriptiveScientificName`

### Core Concepts

| Concept | Variable Pattern | Example |
|---------|-----------------|---------|
| **States** | `*State` | `regimeState`, `volatilityState`, `trendState`, `riskState` |
| **Dimensions** | `*Dimension` | `spatialDimension`, `contextDimension`, `outputDimension` |
| **Weights** | `*Weights` / `*Weight` | `firstLayerWeights`, `archetypeWeight` |
| **Biases** | `*Biases` / `*Bias` | `firstLayerBiases`, `secondLayerBias` |
| **Activations** | `*Activation` | `firstLayerActivation`, `outputActivation` |
| **Pre-activations** | `*Preactivation` | `firstLayerPreactivation`, `secondLayerPreactivation` |
| **Vectors** | `*Vector` | `semanticContextVector`, `pixelInputVector`, `spatialCoordinateVector` |
| **Gradients** | `*Gradient` | `regimeInfluenceGradient`, `volatilityInfluenceGradient` |
| **Statistics** | `*Mean`, `*Magnitude`, `*Variance` | `firstLayerWeightMean`, `globalWeightMagnitude` |

---

## Method Naming Convention

### Format: `verb[ScientificObject]`

### Operations

| Operation | Prefix | Example |
|-----------|--------|---------|
| **Calculation** | `compute*` | `computeRadialDistance()`, `computeTemperature()` |
| **Transformation** | `apply*` | `applyTanhActivation()`, `applySoftmax()` |
| **Normalization** | `normalize*` | `normalizeCoordinates()`, `normalizeWeights()` |
| **Modulation** | `modulate*` | `modulateRegimeInput()`, `modulateVolatility()` |
| **Blending** | `blend*` | `blendArchetypeOutputs()`, `blendWithStripe()` |
| **Validation** | `validate*` | `validateOutputBounds()`, `validateDependency()` |
| **Access** | `get*` / `set*` | `getRegimeState()`, `setContext()` |

---

## Complete Equation Class Names (1-100)

### Archetype Ontology (1-12)
1. `StableArchetypeLibrary`
2. `ArchetypeLibraryCardinality`
3. `ArchetypeParameterization`
4. `TemporalParameterInvariance`
5. `SemanticArchetypeAssignment`
6. `ArchetypeParameterSourceModel`
7. `GlobalArchetypeParameterLibrary`
8. `ArchetypeFunctionSignature`
9. `SpatialInputDimension`
10. `ContextInputDimension`
11. `OutputColorDimension`
12. `HiddenLayerWidth`

### Spatial Geometry (13-20)
13. `SpatialDomainDefinition`
14. `NormalizedXCoordinate`
15. `NormalizedYCoordinate`
16. `SpatialCoordinateVector`
17. `RadialDistance`
18. `PolarAngle`
19. `VignetteFactor`
20. `GeometricFeatureVector`

### Context Evolution (21-30)
21. `SemanticContextVector`
22. `RegimeStateDynamics`
23. `VolatilityStateDynamics`
24. `TrendStateDynamics`
25. `RiskStateDynamics`
26. `FirstLayerWeightMean`
27. `SecondLayerWeightMean`
28. `GlobalWeightMagnitude`
29. `SignedStochasticExcitation`
30. `UniformRandomDriver`

### Pixel Input Synthesis (31-40)
31. `PixelInputVector`
32. `ModulatedRegimeInput`
33. `ModulatedVolatilityInput`
34. `ModulatedTrendInput`
35. `ModulatedRiskInput`
36. `SignedNoiseFromUnit`
37. `UnitHashOutput`
38. `IntegerMixingHash`
39. `InputBoundsValidation`
40. `InputVectorComposition`

### Neural Evaluation (41-50)
41. `FirstLayerPreactivation`
42. `FirstLayerActivation`
43. `SecondLayerPreactivation`
44. `OutputActivation`
45. `OutputColorComponents`
46. `OutputBoundsValidation`
47. `ArchetypeFunctionDefinition`
48. `ArchetypeOperatorNotation`
49. `ArchetypeDistinctness`
50. `TimeInvariance`

### Controller (51-60)
51. `ControllerLogits`
52. `PerArchetypeLogit`
53. `SoftmaxGating`
54. `ProbabilityNormalization`
55. `ProbabilityNonNegativity`
56. `TemperatureModulation`
57. `DominantArchetypeSelection`
58. `GatingEntropy`
59. `GatingConfidence`
60. `GatingTemporalDifference`

### Blending (61-70)
61. `BlendedOutput`
62. `PerChannelBlending`
63. `BlendedOutputBounds`
64. `HardVsSoftSelection`
65. `MixedSelectionMode`
66. `MixingWeightFromEntropy`
67. `HardSelectionLimit`
68. `SoftSelectionLimit`
69. `FrameMeanOutput`
70. `OutputVariance`

### Semantic Diagnostics (71-80)
71. `OrderArchetypeSemantics`
72. `TurbulenceArchetypeSemantics`
73. `GrowthArchetypeSemantics`
74. `DecayArchetypeSemantics`
75. `BalanceArchetypeSemantics`
76. `RegimeInfluenceGradient`
77. `VolatilityInfluenceGradient`
78. `TrendInfluenceGradient`
79. `RiskInfluenceGradient`
80. `SemanticInfluenceMagnitude`

### Temporal Diagnostics (81-90)
81. `ContextStateTransition`
82. `GatingStateTransition`
83. `OutputTemporalUpdate`
84. `OutputTemporalDifference`
85. `ContextTemporalDifference`
86. `OutputStabilityBound`
87. `GatingStabilityBound`
88. `CombinedStabilityBound`
89. `SmallDriftImplication`
90. `ArchetypeIdentityPersistence`

### Final Color Synthesis (91-100)
91. `StripeModulationPattern`
92. `RedChannelSynthesis`
93. `GreenChannelSynthesis`
94. `BlueChannelSynthesis`
95. `FinalColorVector`
96. `BitColorQuantization`
97. `PBOTextureUpload`
98. `TextureUpdate`
99. `FramePresentation`
100. `CompleteRendererSummary`

---

## Dependency Graph Naming

| Old Name | New Name | Meaning |
|----------|----------|---------|
| `s_upstream` | `upstreamEquationIndices` | Array of equation numbers this equation depends on |
| `s_downstream` | `downstreamEquationIndices` | Array of equation numbers that depend on this equation |
| `m_numUpstream` | `m_numUpstreamEquations` | Count of upstream dependencies |
| `m_numDownstream` | `m_numDownstreamEquations` | Count of downstream dependencies |

---

## Context Accessor Naming

| Old Name | New Name | Purpose |
|----------|----------|---------|
| `getCtxRegime()` | `getRegimeState()` | Get regime component of context vector |
| `getCtxVolatility()` | `getVolatilityState()` | Get volatility component |
| `getCtxTrend()` | `getTrendState()` | Get trend component |
| `getCtxRisk()` | `getRiskState()` | Get risk component |
| `setContext()` | `setContext()` | Set all four context components |
| `getW1()` | `getFirstLayerWeights()` | Get first layer weight matrix |
| `getB1()` | `getFirstLayerBiases()` | Get first layer bias vector |
| `getW2()` | `getSecondLayerWeights()` | Get second layer weight matrix |
| `getB2()` | `getSecondLayerBiases()` | Get second layer bias vector |
| `getTemperature()` | `getSoftmaxTemperature()` | Get softmax temperature parameter |
| `getSelectedArchetype()` | `getSelectedArchetypeIndex()` | Get selected archetype index |

---

## Code Example

### Before (Unclear Naming):
```cpp
class Equation022 {
    bool evaluate(EquationContext& ctx) {
        float k = ctx.getCtxRegime();
        ctx.setOutput(22, "regime", &k, 1);
    }
};
```

### After (Scientific Naming):
```cpp
class RegimeStateDynamics {
    bool evaluate(EquationContext& ctx) {
        // Eq 22: c_t^(r) = tanh(a_r*sin(ω_r*t) + b_r*cos(ν_r*t) + η_t^(r))
        const float regimeState = computeRegimeState(ctx.getPhase(), ctx.getRegimeState());
        ctx.setOutput(22, "regime_state", &regimeState, 1);
        ctx.setContext(regimeState, ctx.getVolatilityState(), 
                      ctx.getTrendState(), ctx.getRiskState());
    }
};
```

---

## Benefits

1. **Self-documenting code** - Class names describe the mathematical concept
2. **Easy navigation** - Find equations by scientific concept
3. **Consistent patterns** - Same naming convention across all 100 equations
4. **Research-ready** - Names match scientific handbook notation
5. **Maintainable** - Clear what each component does without comments

---

## References

- `NAMING_CONVENTIONS.md` - Detailed naming rules
- `stable_archetype_100_equations_scientific_handbook.md` - Scientific descriptions
- `stable_archetype_100_equations_deep_handbook.md` - Deep equation analysis
