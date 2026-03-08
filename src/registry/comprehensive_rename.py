#!/usr/bin/env python3
import re
import os

# Complete renaming mappings
REPLACEMENTS = {
    # Class names (old -> new)
    'class Equation001:': 'class StableArchetypeLibrary:',
    'class Equation002:': 'class ArchetypeLibraryCardinality:',
    'class Equation003:': 'class ArchetypeParameterization:',
    'class Equation004:': 'class TemporalParameterInvariance:',
    'class Equation005:': 'class SemanticArchetypeAssignment:',
    'class Equation006:': 'class ArchetypeParameterSourceModel:',
    'class Equation007:': 'class GlobalArchetypeParameterLibrary:',
    'class Equation008:': 'class ArchetypeFunctionSignature:',
    'class Equation009:': 'class SpatialInputDimension:',
    'class Equation010:': 'class ContextInputDimension:',
    'class Equation011:': 'class OutputColorDimension:',
    'class Equation012:': 'class HiddenLayerWidth:',
    
    # Constructors
    'Equation001()': 'StableArchetypeLibrary()',
    'Equation002()': 'ArchetypeLibraryCardinality()',
    'Equation003()': 'ArchetypeParameterization()',
    'Equation004()': 'TemporalParameterInvariance()',
    'Equation005()': 'SemanticArchetypeAssignment()',
    'Equation006()': 'ArchetypeParameterSourceModel()',
    'Equation007()': 'GlobalArchetypeParameterLibrary()',
    'Equation008()': 'ArchetypeFunctionSignature()',
    'Equation009()': 'SpatialInputDimension()',
    'Equation010()': 'ContextInputDimension()',
    'Equation011()': 'OutputColorDimension()',
    'Equation012()': 'HiddenLayerWidth()',
    
    # Factory functions
    'createEquation001': 'createStableArchetypeLibrary',
    'createEquation002': 'createArchetypeLibraryCardinality',
    'createEquation003': 'createArchetypeParameterization',
    'createEquation004': 'createTemporalParameterInvariance',
    'createEquation005': 'createSemanticArchetypeAssignment',
    'createEquation006': 'createArchetypeParameterSourceModel',
    'createEquation007': 'createGlobalArchetypeParameterLibrary',
    'createEquation008': 'createArchetypeFunctionSignature',
    'createEquation009': 'createSpatialInputDimension',
    'createEquation010': 'createContextInputDimension',
    'createEquation011': 'createOutputColorDimension',
    'createEquation012': 'createHiddenLayerWidth',
}

def process_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    for old, new in REPLACEMENTS.items():
        content = content.replace(old, new)
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    print(f"✓ {filepath}")

# Process Archetype Ontology file
process_file('Equation001_012_ArchetypeOntology.cpp')
print("\nDone with Archetype Ontology!")
