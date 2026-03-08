@echo off
REM Rename Spatial Geometry equations (13-20)
sed -i "s/class Equation013:/class SpatialDomainDefinition:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation014:/class NormalizedXCoordinate:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation015:/class NormalizedYCoordinate:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation016:/class SpatialCoordinateVector:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation017:/class RadialDistance:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation018:/class PolarAngle:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation019:/class VignetteFactor:/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/class Equation020:/class GeometricFeatureVector:/g" Equation013_020_SpatialGeometry.cpp

REM Update constructors
sed -i "s/Equation013()/SpatialDomainDefinition()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation014()/NormalizedXCoordinate()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation015()/NormalizedYCoordinate()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation016()/SpatialCoordinateVector()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation017()/RadialDistance()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation018()/PolarAngle()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation019()/VignetteFactor()/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/Equation020()/GeometricFeatureVector()/g" Equation013_020_SpatialGeometry.cpp

REM Update factory functions
sed -i "s/createEquation013/createSpatialDomainDefinition/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation014/createNormalizedXCoordinate/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation015/createNormalizedYCoordinate/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation016/createSpatialCoordinateVector/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation017/createRadialDistance/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation018/createPolarAngle/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation019/createVignetteFactor/g" Equation013_020_SpatialGeometry.cpp
sed -i "s/createEquation020/createGeometricFeatureVector/g" Equation013_020_SpatialGeometry.cpp
echo "Spatial Geometry renamed"
