// Equation013_020_SpatialGeometry.cpp
// Implementation of Equations 13-20: Spatial Geometry Subsystem
// 
// Scientific naming conventions applied based on:
// - stable_archetype_100_equations_scientific_handbook.md
// - stable_archetype_100_equations_deep_handbook.md

#include "../../include/registry/EquationBase.hpp"
#include <cmath>
#include <cstring>

namespace EquationSystem {

// ============================================================
// Equation 013: Spatial Domain Definition
// Ω = {(i,j) | 0 ≤ i < W, 0 ≤ j < H}
// ============================================================
class SpatialDomainDefinition : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SpatialDomainDefinition() : Equation(
        13,
        "Spatial Domain Definition",
        R"(\Omega = \left\{(i,j) \mid 0 \le i < W,\; 0 \le j < H \right\})",
        "Defines the 2D pixel grid domain",
        "Defines screen resolution constants",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        0,
        2
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Spatial domain definition
        // Ω = {(i,j) | 0 ≤ i < W, 0 ≤ j < H}
        // Defines the 2D pixel grid domain for rendering
        
        const float screenWidth = static_cast<float>(ctx.getWidth());
        const float screenHeight = static_cast<float>(ctx.getHeight());
        
        float spatialDomain[2] = {screenWidth, screenHeight};
        ctx.setOutput(13, "spatial_domain", spatialDomain, 2);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(13);
        
        // Validate: domain dimensions must be positive
        if (out.size < 2) return false;
        if (out.values[0] <= 0.0f || out.values[1] <= 0.0f) return false;
        
        return true;
    }
};

const int SpatialEquation013::upstreamEquationIndices[] = {};
const int SpatialEquation013::downstreamEquationIndices[] = {14, 15};

// ============================================================
// Equation 014: Normalized X Coordinate
// x_p = 2i/(W-1) - 1
// ============================================================
class NormalizedXCoordinate : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    NormalizedXCoordinate() : Equation(
        14,
        "Normalized X Coordinate",
        R"(x_p = \frac{2i}{W-1} - 1)",
        "Maps pixel column to [-1, 1] range",
        "Computes normalized x coordinate per pixel",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        6
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Normalized x coordinate
        // x_p = 2i/(W-1) - 1
        // Maps pixel column index to normalized coordinate in [-1, 1]
        
        const int screenWidth = ctx.getWidth();
        const int pixelColumn = screenWidth / 2;  // Test with center pixel
        
        float normalizedX = 0.0f;
        if (screenWidth > 1) {
            normalizedX = (2.0f * static_cast<float>(pixelColumn) / static_cast<float>(screenWidth - 1)) - 1.0f;
        }
        
        ctx.setOutput(14, "normalized_x_coordinate", &normalizedX, 1);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(14);
        
        // Validate: normalized x must be in [-1, 1]
        if (out.size < 1) return false;
        if (out.values[0] < -1.0f || out.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int SpatialEquation014::upstreamEquationIndices[] = {13};
const int SpatialEquation014::downstreamEquationIndices[] = {16, 17, 18, 20, 31};

// ============================================================
// Equation 015: Normalized Y Coordinate
// y_p = 2j/(H-1) - 1
// ============================================================
class NormalizedYCoordinate : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    NormalizedYCoordinate() : Equation(
        15,
        "Normalized Y Coordinate",
        R"(y_p = \frac{2j}{H-1} - 1)",
        "Maps pixel row to [-1, 1] range",
        "Computes normalized y coordinate per pixel",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        6
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Normalized y coordinate
        // y_p = 2j/(H-1) - 1
        // Maps pixel row index to normalized coordinate in [-1, 1]
        
        const int screenHeight = ctx.getHeight();
        const int pixelRow = screenHeight / 2;  // Test with center pixel
        
        float normalizedY = 0.0f;
        if (screenHeight > 1) {
            normalizedY = (2.0f * static_cast<float>(pixelRow) / static_cast<float>(screenHeight - 1)) - 1.0f;
        }
        
        ctx.setOutput(15, "normalized_y_coordinate", &normalizedY, 1);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(15);
        
        // Validate: normalized y must be in [-1, 1]
        if (out.size < 1) return false;
        if (out.values[0] < -1.0f || out.values[0] > 1.0f) return false;
        
        return true;
    }
};

const int SpatialEquation015::upstreamEquationIndices[] = {13};
const int SpatialEquation015::downstreamEquationIndices[] = {16, 17, 18, 20, 31};

// ============================================================
// Equation 016: Spatial Coordinate Vector
// s_p = [x_p, y_p]^T
// ============================================================
class SpatialCoordinateVector : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    SpatialCoordinateVector() : Equation(
        16,
        "Spatial Coordinate Vector",
        R"(\mathbf{s}_p = \begin{bmatrix} x_p \\ y_p \end{bmatrix})",
        "2D spatial position as vector",
        "Packages x,y into coordinate vector",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Spatial coordinate vector
        // s_p = [x_p, y_p]^T
        // Combines normalized x and y into 2D position vector
        
        const EquationData& xData = ctx.getOutput(14);
        const EquationData& yData = ctx.getOutput(15);
        
        float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        float y = (yData.size >= 1) ? yData.values[0] : 0.0f;
        
        float spatialCoordinateVector[2] = {x, y};
        ctx.setOutput(16, "spatial_coordinate_vector", spatialCoordinateVector, 2);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(16);
        
        // Validate: coordinate vector must have 2 components
        if (out.size < 2) return false;
        
        // Both components must be in [-1, 1]
        if (out.values[0] < -1.0f || out.values[0] > 1.0f) return false;
        if (out.values[1] < -1.0f || out.values[1] > 1.0f) return false;
        
        return true;
    }
};

const int SpatialEquation016::upstreamEquationIndices[] = {14, 15};
const int SpatialEquation016::downstreamEquationIndices[] = {40};

// ============================================================
// Equation 017: Radial Distance
// r_p = sqrt(x_p^2 + y_p^2)
// ============================================================
class RadialDistance : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    RadialDistance() : Equation(
        17,
        "Radial Distance",
        R"(r_p = \sqrt{x_p^2 + y_p^2})",
        "Distance from center of screen",
        "Computes radial distance for vignette",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        3
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Radial distance from center
        // r_p = sqrt(x_p^2 + y_p^2)
        // Computes Euclidean distance from screen center
        
        const EquationData& xData = ctx.getOutput(14);
        const EquationData& yData = ctx.getOutput(15);
        
        float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        float y = (yData.size >= 1) ? yData.values[0] : 0.0f;
        
        const float radialDistance = sqrtf(x * x + y * y);
        ctx.setOutput(17, "radial_distance", &radialDistance, 1);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(17);
        
        // Validate: radial distance must be non-negative
        if (out.size < 1) return false;
        if (out.values[0] < 0.0f) return false;
        
        return true;
    }
};

const int SpatialEquation017::upstreamEquationIndices[] = {14, 15};
const int SpatialEquation017::downstreamEquationIndices[] = {19, 92, 93};

// ============================================================
// Equation 018: Polar Angle
// ϑ_p = atan2(y_p, x_p)
// ============================================================
class PolarAngle : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    PolarAngle() : Equation(
        18,
        "Polar Angle",
        R"(\vartheta_p = \operatorname{atan2}(y_p,x_p))",
        "Angular position in polar coordinates",
        "Computes polar angle (available for patterns)",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        2,
        1
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Polar angle
        // ϑ_p = atan2(y_p, x_p)
        // Computes angular position in polar coordinates
        
        const EquationData& xData = ctx.getOutput(14);
        const EquationData& yData = ctx.getOutput(15);
        
        float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        float y = (yData.size >= 1) ? yData.values[0] : 0.0f;
        
        const float polarAngle = atan2f(y, x);
        ctx.setOutput(18, "polar_angle", &polarAngle, 1);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(18);
        
        // Validate: polar angle must be in [-π, π]
        if (out.size < 1) return false;
        const float pi = 3.14159265359f;
        if (out.values[0] < -pi || out.values[0] > pi) return false;
        
        return true;
    }
};

const int SpatialEquation018::upstreamEquationIndices[] = {14, 15};
const int SpatialEquation018::downstreamEquationIndices[] = {20};

// ============================================================
// Equation 019: Vignette Factor
// v_p = max(0, 1.15 - r_p)
// ============================================================
class VignetteFactor : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    VignetteFactor() : Equation(
        19,
        "Vignette Factor",
        R"(v_p = \max(0, 1.15 - r_p))",
        "Radial falloff for edge darkening",
        "Computes vignette multiplier",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        1,
        2
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Vignette factor
        // v_p = max(0, 1.15 - r_p)
        // Computes radial falloff multiplier for edge darkening
        
        const EquationData& radialData = ctx.getOutput(17);
        const float radialDistance = (radialData.size >= 1) ? radialData.values[0] : 0.0f;
        
        const float vignetteFactorRaw = 1.15f - radialDistance;
        const float vignetteFactor = (vignetteFactorRaw > 0.0f) ? vignetteFactorRaw : 0.0f;
        
        ctx.setOutput(19, "vignette_factor", &vignetteFactor, 1);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(19);
        
        // Validate: vignette factor must be in [0, 1.15]
        if (out.size < 1) return false;
        if (out.values[0] < 0.0f || out.values[0] > 1.15f) return false;
        
        return true;
    }
};

const int SpatialEquation019::upstreamEquationIndices[] = {17};
const int SpatialEquation019::downstreamEquationIndices[] = {92, 93};

// ============================================================
// Equation 020: Geometric Feature Vector
// g_p = [x_p, y_p, r_p, ϑ_p]^T
// ============================================================
class GeometricFeatureVector : public Equation {
private:
    static const int upstreamEquationIndices[];
    static const int downstreamEquationIndices[];

public:
    GeometricFeatureVector() : Equation(
        20,
        "Geometric Feature Vector",
        R"(\mathbf{g}_p = \begin{bmatrix} x_p \\ y_p \\ r_p \\ \vartheta_p \end{bmatrix})",
        "Complete geometric description of pixel position",
        "Packages all geometric features",
        "spatial_geometry",
        "OpenCL",
        upstreamEquationIndices,
        downstreamEquationIndices,
        4,
        0
    ) {}

    bool evaluate(EquationContext& ctx) override {
        // Geometric feature vector
        // g_p = [x_p, y_p, r_p, ϑ_p]^T
        // Combines all geometric descriptors into single vector
        
        const EquationData& xData = ctx.getOutput(14);
        const EquationData& yData = ctx.getOutput(15);
        const EquationData& rData = ctx.getOutput(17);
        const EquationData& thetaData = ctx.getOutput(18);
        
        float x = (xData.size >= 1) ? xData.values[0] : 0.0f;
        float y = (yData.size >= 1) ? yData.values[0] : 0.0f;
        float r = (rData.size >= 1) ? rData.values[0] : 0.0f;
        float theta = (thetaData.size >= 1) ? thetaData.values[0] : 0.0f;
        
        float geometricFeatureVector[4] = {x, y, r, theta};
        ctx.setOutput(20, "geometric_feature_vector", geometricFeatureVector, 4);
        
        return true;
    }

    bool validate(const EquationContext& ctx) const override {
        const EquationData& out = ctx.getOutput(20);
        
        // Validate: geometric feature vector must have 4 components
        if (out.size < 4) return false;
        
        // x, y must be in [-1, 1]
        if (out.values[0] < -1.0f || out.values[0] > 1.0f) return false;
        if (out.values[1] < -1.0f || out.values[1] > 1.0f) return false;
        
        // r must be non-negative
        if (out.values[2] < 0.0f) return false;
        
        return true;
    }
};

const int SpatialEquation020::upstreamEquationIndices[] = {14, 15, 17, 18};
const int SpatialEquation020::downstreamEquationIndices[] = {};

// ============================================================
// Factory functions for Spatial Geometry equations (13-20)
// ============================================================
Equation* createSpatialDomainDefinition() { return new SpatialDomainDefinition(); }
Equation* createNormalizedXCoordinate() { return new NormalizedXCoordinate(); }
Equation* createNormalizedYCoordinate() { return new NormalizedYCoordinate(); }
Equation* createSpatialCoordinateVector() { return new SpatialCoordinateVector(); }
Equation* createRadialDistance() { return new RadialDistance(); }
Equation* createPolarAngle() { return new PolarAngle(); }
Equation* createVignetteFactor() { return new VignetteFactor(); }
Equation* createGeometricFeatureVector() { return new GeometricFeatureVector(); }

}  // namespace EquationSystem
