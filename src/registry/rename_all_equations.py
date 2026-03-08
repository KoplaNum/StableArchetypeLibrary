#!/usr/bin/env python3
import re
import os

# Scientific class names for all 100 equations based on handbooks
EQUATION_CLASS_NAMES = {
    # Archetype Ontology (1-12)
    1: "StableArchetypeLibrary",
    2: "ArchetypeLibraryCardinality",
    3: "ArchetypeParameterization",
    4: "TemporalParameterInvariance",
    5: "SemanticArchetypeAssignment",
    6: "ArchetypeParameterSourceModel",
    7: "GlobalArchetypeParameterLibrary",
    8: "ArchetypeFunctionSignature",
    9: "SpatialInputDimension",
    10: "ContextInputDimension",
    11: "OutputColorDimension",
    12: "HiddenLayerWidth",
    
    # Spatial Geometry (13-20)
    13: "SpatialDomainDefinition",
    14: "NormalizedXCoordinate",
    15: "NormalizedYCoordinate",
    16: "SpatialCoordinateVector",
    17: "RadialDistance",
    18: "PolarAngle",
    19: "VignetteFactor",
    20: "GeometricFeatureVector",
    
    # Context Evolution (21-30)
    21: "SemanticContextVector",
    22: "RegimeStateDynamics",
    23: "VolatilityStateDynamics",
    24: "TrendStateDynamics",
    25: "RiskStateDynamics",
    26: "FirstLayerWeightMean",
    27: "SecondLayerWeightMean",
    28: "GlobalWeightMagnitude",
    29: "SignedStochasticExcitation",
    30: "UniformRandomDriver",
    
    # Pixel Input Synthesis (31-40)
    31: "PixelInputVector",
    32: "ModulatedRegimeInput",
    33: "ModulatedVolatilityInput",
    34: "ModulatedTrendInput",
    35: "ModulatedRiskInput",
    36: "SignedNoiseFromUnit",
    37: "UnitHashOutput",
    38: "IntegerMixingHash",
    39: "InputBoundsValidation",
    40: "InputVectorComposition",
    
    # Neural Evaluation (41-50)
    41: "FirstLayerPreactivation",
    42: "FirstLayerActivation",
    43: "SecondLayerPreactivation",
    44: "OutputActivation",
    45: "OutputColorComponents",
    46: "OutputBoundsValidation",
    47: "ArchetypeFunctionDefinition",
    48: "ArchetypeOperatorNotation",
    49: "ArchetypeDistinctness",
    50: "TimeInvariance",
    
    # Controller (51-60)
    51: "ControllerLogits",
    52: "PerArchetypeLogit",
    53: "SoftmaxGating",
    54: "ProbabilityNormalization",
    55: "ProbabilityNonNegativity",
    56: "TemperatureModulation",
    57: "DominantArchetypeSelection",
    58: "GatingEntropy",
    59: "GatingConfidence",
    60: "GatingTemporalDifference",
    
    # Blending (61-70)
    61: "BlendedOutput",
    62: "PerChannelBlending",
    63: "BlendedOutputBounds",
    64: "HardVsSoftSelection",
    65: "MixedSelectionMode",
    66: "MixingWeightFromEntropy",
    67: "HardSelectionLimit",
    68: "SoftSelectionLimit",
    69: "FrameMeanOutput",
    70: "OutputVariance",
    
    # Semantic Diagnostics (71-80)
    71: "OrderArchetypeSemantics",
    72: "TurbulenceArchetypeSemantics",
    73: "GrowthArchetypeSemantics",
    74: "DecayArchetypeSemantics",
    75: "BalanceArchetypeSemantics",
    76: "RegimeInfluenceGradient",
    77: "VolatilityInfluenceGradient",
    78: "TrendInfluenceGradient",
    79: "RiskInfluenceGradient",
    80: "SemanticInfluenceMagnitude",
    
    # Temporal Diagnostics (81-90)
    81: "ContextStateTransition",
    82: "GatingStateTransition",
    83: "OutputTemporalUpdate",
    84: "OutputTemporalDifference",
    85: "ContextTemporalDifference",
    86: "OutputStabilityBound",
    87: "GatingStabilityBound",
    88: "CombinedStabilityBound",
    89: "SmallDriftImplication",
    90: "ArchetypeIdentityPersistence",
    
    # Final Color Synthesis (91-100)
    91: "StripeModulationPattern",
    92: "RedChannelSynthesis",
    93: "GreenChannelSynthesis",
    94: "BlueChannelSynthesis",
    95: "FinalColorVector",
    96: "BitColorQuantization",
    97: "PBOTextureUpload",
    98: "TextureUpdate",
    99: "FramePresentation",
    100: "CompleteRendererSummary"
}

def rename_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Replace class names
    for eq_num, class_name in EQUATION_CLASS_NAMES.items():
        # class EquationXXX: -> class ClassName:
        content = re.sub(r'class Equation' + str(eq_num).zfill(3) + r':', 
                        f'class {class_name}:', content)
        # EquationXXX() -> ClassName()
        content = re.sub(r'Equation' + str(eq_num).zfill(3) + r'\(\)', 
                        f'{class_name}()', content)
        # createEquationXXX -> create[ClassName]
        camel_name = ''.join(word.capitalize() for word in re.findall(r'[A-Z][a-z]+', class_name))
        content = re.sub(r'createEquation' + str(eq_num).zfill(3), 
                        f'create{camel_name}', content)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"Renamed: {filepath}")

# Process all equation files
for filename in os.listdir('.'):
    if filename.startswith('Equation') and filename.endswith('.cpp'):
        rename_file(filename)

print("Done renaming all equations!")
