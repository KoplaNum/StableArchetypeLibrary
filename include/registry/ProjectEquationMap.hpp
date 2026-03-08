// ProjectEquationMap.hpp - File path mapping for all 100 equations
// Uses scientific naming - no magic numbers in user code

#ifndef PROJECT_EQUATION_MAP_HPP
#define PROJECT_EQUATION_MAP_HPP

#include "../common/StableArchetypeCommon.hpp"
#include "EquationIdentifiers.hpp"

namespace ProjectEquationMap {

// Get file path for equation header - uses scientific constants internally
inline const char* get_equation_header_path(int eq_num) {
    static const char* paths[] = {
        nullptr,
        "equations/archetype_ontology/Equation001.hpp",      // StableArchetypeLibrary
        "equations/archetype_ontology/Equation002.hpp",      // ArchetypeLibraryCardinality
        "equations/archetype_ontology/Equation003.hpp",      // ArchetypeParameterization
        "equations/archetype_ontology/Equation004.hpp",      // TemporalParameterInvariance
        "equations/archetype_ontology/Equation005.hpp",      // SemanticArchetypeAssignment
        "equations/archetype_ontology/Equation006.hpp",      // ArchetypeParameterSourceModel
        "equations/archetype_ontology/Equation007.hpp",      // GlobalArchetypeParameterLibrary
        "equations/archetype_ontology/Equation008.hpp",      // ArchetypeFunctionSignature
        "equations/archetype_ontology/Equation009.hpp",      // SpatialInputDimension
        "equations/archetype_ontology/Equation010.hpp",      // ContextInputDimension
        "equations/archetype_ontology/Equation011.hpp",      // OutputColorDimension
        "equations/archetype_ontology/Equation012.hpp",      // HiddenLayerWidth
        "equations/spatial_geometry/Equation013.hpp",        // SpatialDomainDefinition
        "equations/spatial_geometry/Equation014.hpp",        // NormalizedXCoordinate
        "equations/spatial_geometry/Equation015.hpp",        // NormalizedYCoordinate
        "equations/spatial_geometry/Equation016.hpp",        // SpatialCoordinateVector
        "equations/spatial_geometry/Equation017.hpp",        // RadialDistance
        "equations/spatial_geometry/Equation018.hpp",        // PolarAngle
        "equations/spatial_geometry/Equation019.hpp",        // VignetteFactor
        "equations/spatial_geometry/Equation020.hpp",        // GeometricFeatureVector
        "equations/context_evolution/Equation021.hpp",       // SemanticContextVector
        "equations/context_evolution/Equation022.hpp",       // RegimeStateDynamics
        "equations/context_evolution/Equation023.hpp",       // VolatilityStateDynamics
        "equations/context_evolution/Equation024.hpp",       // TrendStateDynamics
        "equations/context_evolution/Equation025.hpp",       // RiskStateDynamics
        "equations/context_evolution/Equation026.hpp",       // FirstLayerWeightMean
        "equations/context_evolution/Equation027.hpp",       // SecondLayerWeightMean
        "equations/context_evolution/Equation028.hpp",       // GlobalWeightMagnitude
        "equations/context_evolution/Equation029.hpp",       // SignedStochasticExcitation
        "equations/context_evolution/Equation030.hpp",       // UniformRandomDriver
        "equations/pixel_input_synthesis/Equation031.hpp",   // PixelInputVector
        "equations/pixel_input_synthesis/Equation032.hpp",   // ModulatedRegimeInput
        "equations/pixel_input_synthesis/Equation033.hpp",   // ModulatedVolatilityInput
        "equations/pixel_input_synthesis/Equation034.hpp",   // ModulatedTrendInput
        "equations/pixel_input_synthesis/Equation035.hpp",   // ModulatedRiskInput
        "equations/pixel_input_synthesis/Equation036.hpp",   // SignedNoiseFromUnit
        "equations/pixel_input_synthesis/Equation037.hpp",   // UnitHashOutput
        "equations/pixel_input_synthesis/Equation038.hpp",   // IntegerMixingHash
        "equations/pixel_input_synthesis/Equation039.hpp",   // InputBoundsValidation
        "equations/pixel_input_synthesis/Equation040.hpp",   // InputVectorComposition
        "equations/archetype_neural_evaluation/Equation041.hpp", // FirstLayerPreactivation
        "equations/archetype_neural_evaluation/Equation042.hpp", // FirstLayerActivation
        "equations/archetype_neural_evaluation/Equation043.hpp", // SecondLayerPreactivation
        "equations/archetype_neural_evaluation/Equation044.hpp", // OutputActivation
        "equations/archetype_neural_evaluation/Equation045.hpp", // OutputColorComponents
        "equations/archetype_neural_evaluation/Equation046.hpp", // OutputBoundsValidation
        "equations/archetype_neural_evaluation/Equation047.hpp", // ArchetypeFunctionDefinition
        "equations/archetype_neural_evaluation/Equation048.hpp", // ArchetypeOperatorNotation
        "equations/archetype_neural_evaluation/Equation049.hpp", // ArchetypeDistinctness
        "equations/archetype_neural_evaluation/Equation050.hpp", // TimeInvariance
        "equations/controller_gating/Equation051.hpp",       // ControllerLogits
        "equations/controller_gating/Equation052.hpp",       // PerArchetypeLogit
        "equations/controller_gating/Equation053.hpp",       // SoftmaxGating
        "equations/controller_gating/Equation054.hpp",       // ProbabilityNormalization
        "equations/controller_gating/Equation055.hpp",       // ProbabilityNonNegativity
        "equations/controller_gating/Equation056.hpp",       // TemperatureModulation
        "equations/controller_gating/Equation057.hpp",       // DominantArchetypeSelection
        "equations/controller_gating/Equation058.hpp",       // GatingEntropy
        "equations/controller_gating/Equation059.hpp",       // GatingConfidence
        "equations/controller_gating/Equation060.hpp",       // GatingTemporalDifference
        "equations/blending/Equation061.hpp",                // BlendedOutput
        "equations/blending/Equation062.hpp",                // PerChannelBlending
        "equations/blending/Equation063.hpp",                // BlendedOutputBounds
        "equations/blending/Equation064.hpp",                // HardVsSoftSelection
        "equations/blending/Equation065.hpp",                // MixedSelectionMode
        "equations/blending/Equation066.hpp",                // MixingWeightFromEntropy
        "equations/blending/Equation067.hpp",                // HardSelectionLimit
        "equations/blending/Equation068.hpp",                // SoftSelectionLimit
        "equations/blending/Equation069.hpp",                // FrameMeanOutput
        "equations/blending/Equation070.hpp",                // OutputVariance
        "equations/semantic_diagnostics/Equation071.hpp",    // OrderArchetypeSemantics
        "equations/semantic_diagnostics/Equation072.hpp",    // TurbulenceArchetypeSemantics
        "equations/semantic_diagnostics/Equation073.hpp",    // GrowthArchetypeSemantics
        "equations/semantic_diagnostics/Equation074.hpp",    // DecayArchetypeSemantics
        "equations/semantic_diagnostics/Equation075.hpp",    // BalanceArchetypeSemantics
        "equations/semantic_diagnostics/Equation076.hpp",    // RegimeInfluenceGradient
        "equations/semantic_diagnostics/Equation077.hpp",    // VolatilityInfluenceGradient
        "equations/semantic_diagnostics/Equation078.hpp",    // TrendInfluenceGradient
        "equations/semantic_diagnostics/Equation079.hpp",    // RiskInfluenceGradient
        "equations/semantic_diagnostics/Equation080.hpp",    // SemanticInfluenceMagnitude
        "equations/temporal_diagnostics/Equation081.hpp",    // ContextStateTransition
        "equations/temporal_diagnostics/Equation082.hpp",    // GatingStateTransition
        "equations/temporal_diagnostics/Equation083.hpp",    // OutputTemporalUpdate
        "equations/temporal_diagnostics/Equation084.hpp",    // OutputTemporalDifference
        "equations/temporal_diagnostics/Equation085.hpp",    // ContextTemporalDifference
        "equations/temporal_diagnostics/Equation086.hpp",    // OutputStabilityBound
        "equations/temporal_diagnostics/Equation087.hpp",    // GatingStabilityBound
        "equations/temporal_diagnostics/Equation088.hpp",    // CombinedStabilityBound
      
