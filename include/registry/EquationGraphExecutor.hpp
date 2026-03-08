// EquationGraphExecutor.hpp
// Dependency graph traversal with topological sort
// Executes all 100 equations in correct dependency order

#ifndef EQUATION_GRAPH_EXECUTOR_HPP
#define EQUATION_GRAPH_EXECUTOR_HPP

#include "EquationBase.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>

namespace EquationSystem {

// ============================================================
// Dependency Graph Executor
// ============================================================
class EquationGraphExecutor {
private:
    std::vector<Equation*> m_equations;  // All 100 equations
    std::vector<int> m_evaluationOrder;   // Topologically sorted order
    std::vector<int> m_inDegree;          // Number of unresolved dependencies
    std::vector<std::vector<int>> m_adjList;  // Adjacency list (upstream -> downstream)
    
    bool m_isInitialized;
    bool m_isSorted;
    
    EquationContext* m_context;

public:
    EquationGraphExecutor()
        : m_isInitialized(false)
        , m_isSorted(false)
        , m_context(nullptr)
    {
        m_equations.resize(101, nullptr);  // 1-indexed
        m_inDegree.resize(101, 0);
        m_adjList.resize(101);
    }
    
    ~EquationGraphExecutor() {
        // Don't delete equations - they're statically allocated
        m_equations.clear();
    }
    
    // Register an equation with the graph
    bool registerEquation(Equation* eq) {
        if(!eq) return false;
        
        int num = eq->getNumber();
        if(num < 1 || num > 100) {
            printf("\n[GraphExecutor] Invalid equation number: %d", num);
            return false;
        }
        
        m_equations[num] = eq;
        m_isInitialized = true;
        m_isSorted = false;  // Need to re-sort
        
        return true;
    }
    
    // Build adjacency list and compute in-degrees
    void buildGraph() {
        // Clear existing graph
        for(int i = 0; i <= 100; i++) {
            m_adjList[i].clear();
            m_inDegree[i] = 0;
        }
        
        // Build graph from dependency metadata
        for(int i = 1; i <= 100; i++) {
            Equation* eq = m_equations[i];
            if(!eq) continue;
            
            // For each downstream dependency, add edge and increment in-degree
            for(int j = 0; j < eq->getNumDownstream(); j++) {
                int downstream = eq->getDownstreamDep(j);
                if(downstream >= 1 && downstream <= 100) {
                    m_adjList[i].push_back(downstream);
                    m_inDegree[downstream]++;
                }
            }
        }
    }
    
    // Topological sort using Kahn's algorithm
    bool computeEvaluationOrder() {
        if(!m_isInitialized) {
            printf("\n[GraphExecutor] Cannot sort - equations not registered");
            return false;
        }
        
        buildGraph();
        
        m_evaluationOrder.clear();
        std::queue<int> zeroInDegree;
        
        // Find all equations with no dependencies (in-degree = 0)
        for(int i = 1; i <= 100; i++) {
            if(m_equations[i] && m_inDegree[i] == 0) {
                zeroInDegree.push(i);
            }
        }
        
        // Process queue
        while(!zeroInDegree.empty()) {
            int current = zeroInDegree.front();
            zeroInDegree.pop();
            
            m_evaluationOrder.push_back(current);
            
            // Reduce in-degree of all downstream equations
            for(int downstream : m_adjList[current]) {
                m_inDegree[downstream]--;
                if(m_inDegree[downstream] == 0) {
                    zeroInDegree.push(downstream);
                }
            }
        }
        
        // Check for cycles
        if(m_evaluationOrder.size() < countRegisteredEquations()) {
            printf("\n[GraphExecutor] ERROR: Circular dependency detected!");
            printCycleDiagnostics();
            return false;
        }
        
        m_isSorted = true;
        printf("\n[GraphExecutor] Evaluation order computed: %d equations",
               (int)m_evaluationOrder.size());
        
        return true;
    }
    
    // Execute all equations in dependency order
    bool execute(EquationContext& ctx) {
        if(!m_isSorted) {
            printf("\n[GraphExecutor] Computing evaluation order...");
            if(!computeEvaluationOrder()) {
                printf("\n[GraphExecutor] Failed to compute evaluation order!");
                return false;
            }
        }
        
        m_context = &ctx;
        int successCount = 0;
        int skipCount = 0;
        int failCount = 0;
        
        printf("\n[GraphExecutor] Executing %d equations...",
               (int)m_evaluationOrder.size());
        
        for(int eqNum : m_evaluationOrder) {
            Equation* eq = m_equations[eqNum];
            if(!eq) continue;
            
            // Check if upstream dependencies are satisfied
            bool upstreamReady = true;
            for(int i = 0; i < eq->getNumUpstream(); i++) {
                int upstream = eq->getUpstreamDep(i);
                if(upstream >= 1 && upstream <= 100) {
                    if(m_equations[upstream] && !m_equations[upstream]->isEvaluated()) {
                        // Upstream not evaluated yet - this shouldn't happen with topo sort
                        printf("\n[GraphExecutor] Eq %d: upstream %d not ready!",
                               eqNum, upstream);
                        upstreamReady = false;
                    }
                }
            }
            
            if(!upstreamReady) {
                eq->markEvaluated(EQ_EVALUATION_ERROR);
                ctx.recordEvaluation(false);
                failCount++;
                continue;
            }
            
            // Check if this equation should be skipped (optional equations)
            bool shouldSkip = !shouldEvaluate(eq, ctx);
            
            if(shouldSkip) {
                eq->markEvaluated(EQ_EVALUATED_SKIP);
                ctx.recordEvaluation(false, true);
                skipCount++;
                continue;
            }
            
            // Evaluate the equation
            bool success = eq->evaluate(ctx);
            
            if(success) {
                // Validate results
                bool valid = eq->validate(ctx);
                if(valid) {
                    eq->markEvaluated(EQ_EVALUATED_OK);
                    ctx.recordEvaluation(true);
                    successCount++;
                } else {
                    printf("\n[GraphExecutor] Eq %d (%s): validation FAILED",
                           eqNum, eq->getTitle());
                    eq->markEvaluated(EQ_EVALUATION_ERROR);
                    ctx.recordEvaluation(false);
                    failCount++;
                }
            } else {
                printf("\n[GraphExecutor] Eq %d (%s): evaluation FAILED",
                       eqNum, eq->getTitle());
                eq->markEvaluated(EQ_EVALUATION_ERROR);
                ctx.recordEvaluation(false);
                failCount++;
            }
        }
        
        printf("\n[GraphExecutor] Complete: %d OK, %d skipped, %d failed",
               successCount, skipCount, failCount);
        
        m_context = nullptr;
        return (failCount == 0);
    }
    
    // Reset all equations for next frame
    void reset() {
        for(int i = 1; i <= 100; i++) {
            if(m_equations[i]) {
                m_equations[i]->reset();
            }
        }
        m_isSorted = false;  // May need to re-sort if dependencies changed
    }
    
    // Diagnostics
    void printGraphDiagnostics() const {
        printf("\n\n=== Dependency Graph Diagnostics ===");
        printf("\nRegistered equations: %d", countRegisteredEquations());
        printf("\nEvaluation order size: %d", (int)m_evaluationOrder.size());
        
        // Print equations by subsystem
        const char* subsystems[] = {
            "archetype_ontology", "spatial_geometry", "context_evolution",
            "pixel_input_synthesis", "archetype_neural_evaluation",
            "controller_gating", "blending", "semantic_diagnostics",
            "temporal_diagnostics", "final_color_synthesis"
        };
        
        for(int s = 0; s < 10; s++) {
            printf("\n\n%s:", subsystems[s]);
            int count = 0;
            for(int i = 1; i <= 100; i++) {
                if(m_equations[i] && strcmp(m_equations[i]->getSubsystem(), subsystems[s]) == 0) {
                    printf(" %d", i);
                    count++;
                }
            }
            if(count == 0) printf(" (none)");
        }
        
        // Print dependency chains
        printf("\n\n=== Critical Dependency Chains ===");
        printDependencyChain(1, 100);  // Eq 1 to Eq 100
    }
    
    void printDependencyChain(int from, int to) const {
        printf("\nPath from Eq %d to Eq %d:", from, to);
        
        std::vector<int> path;
        std::vector<bool> visited(101, false);
        
        if(findPath(from, to, path, visited)) {
            for(size_t i = 0; i < path.size(); i++) {
                printf(" %d", path[i]);
                if(i < path.size() - 1) printf(" ->");
            }
        } else {
            printf(" (no direct path)");
        }
    }
    
    // Validation
    bool validateGraph() const {
        // Check for cycles
        std::vector<int> order;
        std::vector<int> inDegree(101, 0);
        
        // Compute in-degrees
        for(int i = 1; i <= 100; i++) {
            if(!m_equations[i]) continue;
            for(int j = 0; j < m_equations[i]->getNumDownstream(); j++) {
                int downstream = m_equations[i]->getDownstreamDep(j);
                if(downstream >= 1 && downstream <= 100) {
                    inDegree[downstream]++;
                }
            }
        }
        
        // Try to find topological order
        std::queue<int> q;
        for(int i = 1; i <= 100; i++) {
            if(m_equations[i] && inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            
            if(m_equations[u]) {
                for(int j = 0; j < m_equations[u]->getNumDownstream(); j++) {
                    int v = m_equations[u]->getDownstreamDep(j);
                    if(v >= 1 && v <= 100) {
                        inDegree[v]--;
                        if(inDegree[v] == 0) {
                            q.push(v);
                        }
                    }
                }
            }
        }
        
        // If we couldn't order all equations, there's a cycle
        int registeredCount = countRegisteredEquations();
        if(order.size() < (size_t)registeredCount) {
            printf("\n[GraphExecutor] VALIDATION FAILED: Circular dependency detected!");
            return false;
        }
        
        printf("\n[GraphExecutor] Graph validation PASSED (no cycles, %d equations)",
               (int)order.size());
        return true;
    }
    
    // Get evaluation order for inspection
    const std::vector<int>& getEvaluationOrder() const {
        return m_evaluationOrder;
    }
    
    Equation* getEquation(int num) {
        return (num >= 1 && num <= 100) ? m_equations[num] : nullptr;
    }

private:
    int countRegisteredEquations() const {
        int count = 0;
        for(int i = 1; i <= 100; i++) {
            if(m_equations[i]) count++;
        }
        return count;
    }
    
    bool shouldEvaluate(Equation* eq, const EquationContext& ctx) const {
        // Override this for conditional equation execution
        // For now, evaluate all registered equations
        (void)eq;
        (void)ctx;
        return true;
    }
    
    bool findPath(int from, int to, std::vector<int>& path,
                  std::vector<bool>& visited) const {
        if(from == to) {
            path.push_back(from);
            return true;
        }
        
        visited[from] = true;
        path.push_back(from);
        
        if(m_equations[from]) {
            for(int i = 0; i < m_equations[from]->getNumDownstream(); i++) {
                int next = m_equations[from]->getDownstreamDep(i);
                if(next >= 1 && next <= 100 && !visited[next]) {
                    if(findPath(next, to, path, visited)) {
                        return true;
                    }
                }
            }
        }
        
        path.pop_back();
        return false;
    }
    
    void printCycleDiagnostics() const {
        printf("\n[GraphExecutor] Looking for cycles...");
        
        // Find equations that couldn't be ordered
        int unsortedCount = 0;
        for(int i = 1; i <= 100; i++) {
            if(m_equations[i]) {
                bool inOrder = false;
                for(int eqNum : m_evaluationOrder) {
                    if(eqNum == i) {
                        inOrder = true;
                        break;
                    }
                }
                if(!inOrder) {
                    printf("\n  Eq %d (%s) not in evaluation order",
                           i, m_equations[i]->getTitle());
                    unsortedCount++;
                }
            }
        }
        
        if(unsortedCount > 0) {
            printf("\n[GraphExecutor] %d equations involved in potential cycle",
                   unsortedCount);
        }
    }
};

}  // namespace EquationSystem

#endif
