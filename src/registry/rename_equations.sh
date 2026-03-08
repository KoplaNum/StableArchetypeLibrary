#!/bin/bash
# Rename Equation classes to meaningful scientific names

# Archetype Ontology (1-12)
sed -i 's/class Equation001:/class StableArchetypeLibrary:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation002:/class ArchetypeLibraryCardinality:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation003:/class ArchetypeParameterization:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation004:/class TemporalParameterInvariance:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation005:/class SemanticArchetypeAssignment:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation006:/class ArchetypeParameterSourceModel:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation007:/class GlobalArchetypeParameterLibrary:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation008:/class ArchetypeFunctionSignature:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation009:/class SpatialInputDimension:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation010:/class ContextInputDimension:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation011:/class OutputColorDimension:/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/class Equation012:/class HiddenLayerWidth:/g' Equation001_012_ArchetypeOntology.cpp

# Update constructor calls
sed -i 's/Equation001()/StableArchetypeLibrary()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation002()/ArchetypeLibraryCardinality()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation003()/ArchetypeParameterization()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation004()/TemporalParameterInvariance()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation005()/SemanticArchetypeAssignment()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation006()/ArchetypeParameterSourceModel()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation007()/GlobalArchetypeParameterLibrary()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation008()/ArchetypeFunctionSignature()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation009()/SpatialInputDimension()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation010()/ContextInputDimension()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation011()/OutputColorDimension()/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/Equation012()/HiddenLayerWidth()/g' Equation001_012_ArchetypeOntology.cpp

# Update factory functions
sed -i 's/createEquation001/createStableArchetypeLibrary/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation002/createArchetypeLibraryCardinality/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation003/createArchetypeParameterization/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation004/createTemporalParameterInvariance/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation005/createSemanticArchetypeAssignment/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation006/createArchetypeParameterSourceModel/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation007/createGlobalArchetypeParameterLibrary/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation008/createArchetypeFunctionSignature/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation009/createSpatialInputDimension/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation010/createContextInputDimension/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation011/createOutputColorDimension/g' Equation001_012_ArchetypeOntology.cpp
sed -i 's/createEquation012/createHiddenLayerWidth/g' Equation001_012_ArchetypeOntology.cpp

echo "Renamed Archetype Ontology equations (1-12)"
