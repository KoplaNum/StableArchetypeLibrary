// EquationIdentifiers.hpp
// Scientific equation identifiers with meaningful names
// Based on: stable_archetype_100_equations_scientific_handbook.md
//
// All equation numbers replaced with scientifically meaningful constants

#ifndef EQUATION_IDENTIFIERS_HPP
#define EQUATION_IDENTIFIERS_HPP

namespace EquationSystem {
namespace EquationID {

// ============================================================
// Archetype Ontology (Equations 1-12)
// ============================================================
constexpr int STABLE_ARCHETYPE_LIBRARY = 1;
constexpr int ARCHETYPE_LIBRARY_CARDINALITY = 2;
constexpr int ARCHETYPE_PARAMETERIZATION = 3;
constexpr int TEMPORAL_PARAMETER_INVARIANCE = 4;
constexpr int SEMANTIC_ARCHETYPE_ASSIGNMENT = 5;
constexpr int ARCHETYPE_PARAMETER_SOURCE_MODEL = 6;
constexpr int GLOBAL_ARCHETYPE_PARAMETER_LIBRARY = 7;
constexpr int ARCHETYPE_FUNCTION_SIGNATURE = 8;
constexpr int SPATIAL_INPUT_DIMENSION = 9;
constexpr int CONTEXT_INPUT_DIMENSION = 10;
constexpr int OUTPUT_COLOR_DIMENSION = 11;
constexpr int HIDDEN_LAYER_WIDTH = 12;

// ============================================================
// Spatial Geometry (Equations 13-20)
// ============================================================
constexpr int SPATIAL_DOMAIN_DEFINITION = 13;
constexpr int NORMALIZED_X_COORDINATE = 14;
constexpr int NORMALIZED_Y_COORDINATE = 15;
constexpr int SPATIAL_COORDINATE_VECTOR = 16;
constexpr int RADIAL_DISTANCE = 17;
constexpr int POLAR_ANGLE = 18;
constexpr int VIGNETTE_FACTOR = 19;
constexpr int GEOMETRIC_FEATURE_VECTOR = 20;

// ============================================================
// Context Evolution (Equations 21-30)
// ============================================================
constexpr int SEMANTIC_CONTEXT_VECTOR = 21;
constexpr int REGIME_STATE_DYNAMICS = 22;
constexpr int VOLATILITY_STATE_DYNAMICS = 23;
constexpr int TREND_STATE_DYNAMICS = 24;
constexpr int RISK_STATE_DYNAMICS = 25;
constexpr int FIRST_LAYER_WEIGHT_MEAN = 26;
constexpr int SECOND_LAYER_WEIGHT_MEAN = 27;
constexpr int GLOBAL_WEIGHT_MAGNITUDE = 28;
constexpr int SIGNED_STOCHASTIC_EXCITATION = 29;
constexpr int UNIFORM_RANDOM_DRIVER = 30;

// ============================================================
// Pixel Input Synthesis (Equations 31-40)
// ============================================================
constexpr int PIXEL_INPUT_VECTOR = 31;
constexpr int MODULATED_REGIME_INPUT = 32;
constexpr int MODULATED_VOLATILITY_INPUT = 33;
constexpr int MODULATED_TREND_INPUT = 34;
constexpr int MODULATED_RISK_INPUT = 35;
constexpr int SIGNED_NOISE_FROM_UNIT = 36;
constexpr int UNIT_HASH_OUTPUT = 37;
constexpr int INTEGER_MIXING_HASH = 38;
constexpr int INPUT_BOUNDS_VALIDATION = 39;
constexpr int INPUT_VECTOR_COMPOSITION = 40;

// ============================================================
// Archetype Neural Evaluation (Equations 41-50)
// ============================================================
constexpr int FIRST_LAYER_PREACTIVATION = 41;
constexpr int FIRST_LAYER_ACTIVATION = 42;
constexpr int SECOND_LAYER_PREACTIVATION = 43;
constexpr int OUTPUT_ACTIVATION = 44;
constexpr int OUTPUT_COLOR_COMPONENTS = 45;
constexpr int OUTPUT_BOUNDS_VALIDATION = 46;
constexpr int ARCHETYPE_FUNCTION_DEFINITION = 47;
constexpr int ARCHETYPE_OPERATOR_NOTATION = 48;
constexpr int ARCHETYPE_DISTINCTNESS = 49;
constexpr int TIME_INVARIANCE = 50;

// ============================================================
// Controller/Gating (Equations 51-60)
// ============================================================
constexpr int CONTROLLER_LOGITS = 51;
constexpr int PER_ARCHETYPE_LOGIT = 52;
constexpr int SOFTMAX_GATING = 53;
constexpr int PROBABILITY_NORMALIZATION = 54;
constexpr int PROBABILITY_NON_NEGATIVITY = 55;
constexpr int TEMPERATURE_MODULATION = 56;
constexpr int DOMINANT_ARCHETYPE_SELECTION = 57;
constexpr int GATING_ENTROPY = 58;
constexpr int GATING_CONFIDENCE = 59;
constexpr int GATING_TEMPORAL_DIFFERENCE = 60;

// ============================================================
// Blending (Equations 61-70)
// ============================================================
constexpr int BLENDED_OUTPUT = 61;
constexpr int PER_CHANNEL_BLENDING = 62;
constexpr int BLENDED_OUTPUT_BOUNDS = 63;
constexpr int HARD_VS_SOFT_SELECTION = 64;
constexpr int MIXED_SELECTION_MODE = 65;
constexpr int MIXING_WEIGHT_FROM_ENTROPY = 66;
constexpr int HARD_SELECTION_LIMIT = 67;
constexpr int SOFT_SELECTION_LIMIT = 68;
constexpr int FRAME_MEAN_OUTPUT = 69;
constexpr int OUTPUT_VARIANCE = 70;

// ============================================================
// Semantic Diagnostics (Equations 71-80)
// ============================================================
constexpr int ORDER_ARCHETYPE_SEMANTICS = 71;
constexpr int TURBULENCE_ARCHETYPE_SEMANTICS = 72;
constexpr int GROWTH_ARCHETYPE_SEMANTICS = 73;
constexpr int DECAY_ARCHETYPE_SEMANTICS = 74;
constexpr int BALANCE_ARCHETYPE_SEMANTICS = 75;
constexpr int REGIME_INFLUENCE_GRADIENT = 76;
constexpr int VOLATILITY_INFLUENCE_GRADIENT = 77;
constexpr int TREND_INFLUENCE_GRADIENT = 78;
constexpr int RISK_INFLUENCE_GRADIENT = 79;
constexpr int SEMANTIC_INFLUENCE_MAGNITUDE = 80;

// ============================================================
// Temporal Diagnostics (Equations 81-90)
// ============================================================
constexpr int CONTEXT_STATE_TRANSITION = 81;
constexpr int GATING_STATE_TRANSITION = 82;
constexpr int OUTPUT_TEMPORAL_UPDATE = 83;
constexpr int OUTPUT_TEMPORAL_DIFFERENCE = 84;
constexpr int CONTEXT_TEMPORAL_DIFFERENCE = 85;
constexpr int OUTPUT_STABILITY_BOUND = 86;
constexpr int GATING_STABILITY_BOUND = 87;
constexpr int COMBINED_STABILITY_BOUND = 88;
constexpr int SMALL_DRIFT_IMPLICATION = 89;
constexpr int ARCHETYPE_IDENTITY_PERSISTENCE = 90;

// ============================================================
// Final Color Synthesis (Equations 91-100)
// ============================================================
constexpr int STRIPE_MODULATION_PATTERN = 91;
constexpr int RED_CHANNEL_SYNTHESIS = 92;
constexpr int GREEN_CHANNEL_SYNTHESIS = 93;
constexpr int BLUE_CHANNEL_SYNTHESIS = 94;
constexpr int FINAL_COLOR_VECTOR = 95;
constexpr int BIT8_COLOR_QUANTIZATION = 96;
constexpr int PBO_TEXTURE_UPLOAD = 97;
constexpr int TEXTURE_UPDATE = 98;
constexpr int FRAME_PRESENTATION = 99;
constexpr int COMPLETE_RENDERER_SUMMARY = 100;

}  // namespace EquationID

// ============================================================
// Output String Identifiers (Scientific Naming)
// ============================================================
namespace OutputName {

// Archetype Ontology
constexpr const char* ARCHETYPE_LIBRARY = "archetype_library_metadata";
constexpr const char* LIBRARY_CARDINALITY = "library_cardinality_count";
constexpr const char* ARCHETYPE_PARAMETER_PACK = "archetype_parameter_pack_valid";
constexpr const char* TEMPORAL_INVARIANCE = "temporal_parameter_invariance_flag";
constexpr const char* SEMANTIC_ASSIGNMENT = "semantic_archetype_assignment";
constexpr const char* PARAMETER_SOURCE = "parameter_source_model";
constexpr const char* GLOBAL_LIBRARY = "global_parameter_library_ready";
constexpr const char* IO_DIMENSIONS = "archetype_io_dimensions";
constexpr const char* SPATIAL_DIM = "spatial_input_dimension";
constexpr const char* CONTEXT_DIM = "context_input_dimension";
constexpr const char* OUTPUT_DIM = "output_color_dimension";
constexpr const char* HIDDEN_DIM = "hidden_layer_dimensions";

// Spatial Geometry
constexpr const char* SPATIAL_DOMAIN = "spatial_domain_resolution";
constexpr const char* NORM_X = "normalized_x_coordinate";
constexpr const char* NORM_Y = "normalized_y_coordinate";
constexpr const char* SPATIAL_COORD = "spatial_coordinate_vector";
constexpr const char* RADIAL_DIST = "radial_distance_from_center";
constexpr const char* POLAR_ANG = "polar_angle_radians";
constexpr const char* VIGNETTE = "vignette_falloff_factor";
constexpr const char* GEO_FEATURES = "geometric_feature_vector";

// Context Evolution
constexpr const char* CONTEXT_VEC = "semantic_context_vector";
constexpr const char* REGIME = "regime_state_component";
constexpr const char* VOLATILITY = "volatility_state_component";
constexpr const char* TREND = "trend_state_component";
constexpr const char* RISK = "risk_state_component";
constexpr const char* W1_MEAN = "first_layer_weight_mean";
constexpr const char* W2_MEAN = "second_layer_weight_mean";
constexpr const char* WEIGHT_MAG = "global_weight_magnitude";
constexpr const char* SIGNED_NOISE = "signed_stochastic_excitation";
constexpr const char* UNIT_RANDOM = "uniform_random_driver";

// Neural Evaluation
constexpr const char* H1_PREACT = "first_layer_preactivation";
constexpr const char* H1_ACT = "first_layer_activation_tanh";
constexpr const char* H2_PREACT = "second_layer_preactivation";
constexpr const char* OUTPUT_ACT = "output_activation_scaled_tanh";
constexpr const char* RGB_COMP = "rgb_color_components";
constexpr const char* OUTPUT_BOUNDS = "output_bounds_valid";
constexpr const char* ARCH_FUNC = "archetype_function_defined";
constexpr const char* ARCH_OPER = "archetype_operator_notation";
constexpr const char* ARCH_DIST = "archetypes_distinct_flag";
constexpr const char* TIME_INV = "time_invariance_satisfied";

// Controller
constexpr const char* LOGITS = "controller_logits_vector";
constexpr const char* LOGIT_K = "per_archetype_logit";
constexpr const char* SOFTMAX = "softmax_gating_weights";
constexpr const char* PROB_NORM = "probability_normalization_valid";
constexpr const char* PROB_NONNEG = "probability_nonnegativity_valid";
constexpr const char* TEMPERATURE = "softmax_temperature_adaptive";
constexpr const char* SELECTED = "dominant_archetype_index";
constexpr const char* ENTROPY = "gating_entropy_shannon";
constexpr const char* CONFIDENCE = "gating_confidence_normalized";
constexpr const char* GATING_DIFF = "gating_temporal_l1_difference";

// Blending
constexpr const char* BLENDED = "blended_output_rgb";
constexpr const char* CHANNEL_BLEND = "per_channel_blending";
constexpr const char* BLENDED_BOUNDS = "blended_output_bounds_valid";
constexpr const char* SEL_MODE = "hard_vs_soft_selection_mode";
constexpr const char* MIX_MODE = "mixed_selection_lambda";
constexpr const char* MIX_LAMBDA = "mixing_weight_from_entropy";
constexpr const char* HARD_LIM = "hard_selection_limit_behavior";
constexpr const char* SOFT_LIM = "soft_selection_limit_behavior";
constexpr const char* FRAME_MEAN = "frame_mean_output_rgb";
constexpr const char* VARIANCE = "output_spatial_variance";
constexpr const char* ORDER_ARCHETYPE_SEMANTICS = "order_archetype_semantics";
constexpr const char* TURBULENCE_ARCHETYPE_SEMANTICS = "turbulence_archetype_semantics";
constexpr const char* GROWTH_ARCHETYPE_SEMANTICS = "growth_archetype_semantics";
constexpr const char* DECAY_ARCHETYPE_SEMANTICS = "decay_archetype_semantics";
constexpr const char* BALANCE_ARCHETYPE_SEMANTICS = "balance_archetype_semantics";
constexpr const char* REGIME_INFLUENCE_GRADIENT = "regime_influence_gradient_rgb";
constexpr const char* VOLATILITY_INFLUENCE_GRADIENT = "volatility_influence_gradient_rgb";
constexpr const char* TREND_INFLUENCE_GRADIENT = "trend_influence_gradient_rgb";
constexpr const char* RISK_INFLUENCE_GRADIENT = "risk_influence_gradient_rgb";
constexpr const char* SEMANTIC_INFLUENCE_MAGNITUDE = "semantic_influence_magnitudes";

// Temporal Diagnostics
constexpr const char* OUTPUT_TEMPORAL_UPDATE = "output_temporal_update_complete";
constexpr const char* OUTPUT_TEMPORAL_DIFFERENCE = "output_temporal_l1_difference";
constexpr const char* CONTEXT_TEMPORAL_DIFFERENCE = "context_temporal_l2_difference";
constexpr const char* OUTPUT_STABILITY_BOUND = "output_stability_lipschitz_constant";
constexpr const char* GATING_STABILITY_BOUND = "gating_stability_lipschitz_constant";
constexpr const char* COMBINED_STABILITY_BOUND = "combined_stability_lipschitz_constant";
constexpr const char* SMALL_DRIFT_IMPLICATION = "small_drift_implication_valid";
constexpr const char* ARCHETYPE_IDENTITY_PERSISTENCE = "archetype_identity_persistence_valid";

// Color Synthesis
constexpr const char* STRIPE = "stripe_modulation_pattern";
constexpr const char* RED = "red_channel_final_synthesis";
constexpr const char* GREEN = "green_channel_final_synthesis";
constexpr const char* BLUE = "blue_channel_final_synthesis";
constexpr const char* COLOR_VEC = "final_color_vector_rgb";
constexpr const char* QUANTIZED = "8bit_quantized_color";
constexpr const char* PBO_UPLOAD = "pbo_texture_upload_complete";
constexpr const char* TEX_UPDATE = "texture_update_complete";
constexpr const char* FRAME_PRESENTATION = "frame_presentation_complete";
constexpr const char* RENDERER = "complete_renderer_summary";

}  // namespace OutputName

}  // namespace EquationSystem

#endif
