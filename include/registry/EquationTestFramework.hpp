// EquationTestFramework.hpp
// Automated testing and validation for all 100 equations
// Verifies logic, dependencies, and result accuracy

#ifndef EQUATION_TEST_FRAMEWORK_HPP
#define EQUATION_TEST_FRAMEWORK_HPP

#include "EquationBase.hpp"
#include "EquationGraphExecutor.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>

namespace EquationSystem {

// ============================================================
// Test Result Structure
// ============================================================
struct TestResult {
    int equationNumber;
    const char* equationTitle;
    bool passed;
    bool validationPassed;
    double executionTimeMs;
    const char* errorMessage;
    
    TestResult()
        : equationNumber(0)
        , equationTitle(nullptr)
        , passed(false)
        , validationPassed(false)
        , executionTimeMs(0.0)
        , errorMessage(nullptr)
    {}
};

// ============================================================
// Test Framework
// ============================================================
class EquationTestFramework {
private:
    std::vector<TestResult> m_testResults;
    int m_totalTests;
    int m_passedTests;
    int m_failedTests;
    
    EquationContext m_testContext;
    EquationGraphExecutor m_executor;

public:
    EquationTestFramework()
        : m_totalTests(0)
        , m_passedTests(0)
        , m_failedTests(0)
    {}
    
    // Register all equations for testing
    void registerEquations(Equation** equations, int count) {
        for(int i = 0; i < count; i++) {
            if(equations[i]) {
                m_executor.registerEquation(equations[i]);
            }
        }
    }
    
    // Run single equation test
    TestResult testEquation(Equation& eq, EquationContext& ctx) {
        TestResult result;
        result.equationNumber = eq.getNumber();
        result.equationTitle = eq.getTitle();
        
        printf("\n[Test] Eq %d: %s", eq.getNumber(), eq.getTitle());
        
        // Check upstream dependencies
        bool depsReady = true;
        for(int i = 0; i < eq.getNumUpstream(); i++) {
            int upstream = eq.getUpstreamDep(i);
            if(upstream >= 1 && upstream <= 100) {
                if(!m_executor.getEquation(upstream)->isEvaluated()) {
                    printf("\n  [Test] Upstream Eq %d not evaluated!", upstream);
                    depsReady = false;
                }
            }
        }
        
        if(!depsReady) {
            result.passed = false;
            result.errorMessage = "Upstream dependencies not satisfied";
            m_failedTests++;
            return result;
        }
        
        // Execute equation
        double startTime = getTimestamp();
        bool evalSuccess = eq.evaluate(ctx);
        double endTime = getTimestamp();
        
        result.executionTimeMs = (endTime - startTime) * 1000.0;
        
        // Validate results
        bool validationSuccess = false;
        if(evalSuccess) {
            validationSuccess = eq.validate(ctx);
        }
        
        result.validationPassed = validationSuccess;
        result.passed = evalSuccess && validationSuccess;
        
        if(result.passed) {
            printf("  PASS (%.3f ms)", result.executionTimeMs);
            m_passedTests++;
        } else {
            printf("  FAIL (%.3f ms)", result.executionTimeMs);
            if(!evalSuccess) {
                result.errorMessage = "Evaluation failed";
                printf(" - Evaluation returned false");
            } else if(!validationSuccess) {
                result.errorMessage = "Validation failed";
                printf(" - Validation returned false");
            }
            m_failedTests++;
        }
        
        m_testResults.push_back(result);
        m_totalTests++;
        
        return result;
    }
    
    // Run full suite test
    bool runFullSuite() {
        printf("\n\n========================================");
        printf("\n Stable Archetype Library - Test Suite");
        printf("\n 100 Equations Dependency Graph Validation");
        printf("\n========================================");
        
        m_testResults.clear();
        m_totalTests = 0;
        m_passedTests = 0;
        m_failedTests = 0;
        
        // Validate graph structure first
        printf("\n\n[Suite] Validating dependency graph...");
        if(!m_executor.validateGraph()) {
            printf("\n[Suite] Graph validation FAILED - circular dependencies detected!");
            return false;
        }
        
        // Compute evaluation order
        printf("\n[Suite] Computing evaluation order...");
        if(!m_executor.computeEvaluationOrder()) {
            printf("\n[Suite] Failed to compute evaluation order!");
            return false;
        }
        
        // Execute all equations through graph
        printf("\n[Suite] Executing all equations...");
        bool execSuccess = m_executor.execute(m_testContext);
        
        if(!execSuccess) {
            printf("\n[Suite] Execution completed with errors");
        }
        
        // Print detailed results
        printTestReport();
        
        return execSuccess;
    }
    
    // Test specific subsystem
    bool runSubsystemTest(const char* subsystem) {
        printf("\n\n[Subsystem Test] %s", subsystem);
        
        int count = 0;
        int passed = 0;
        
        for(int i = 1; i <= 100; i++) {
            Equation* eq = m_executor.getEquation(i);
            if(eq && strcmp(eq->getSubsystem(), subsystem) == 0) {
                TestResult result = testEquation(*eq, m_testContext);
                if(result.passed) passed++;
                count++;
            }
        }
        
        printf("\n[Subsystem Test] %s: %d/%d passed",
               subsystem, passed, count);
        
        return (passed == count);
    }
    
    // Test dependency chain
    bool testDependencyChain(int fromEq, int toEq) {
        printf("\n\n[Dependency Chain Test] Eq %d -> Eq %d", fromEq, toEq);
        
        // Reset context
        m_testContext = EquationContext();
        
        // Execute only equations in path
        std::vector<int> path;
        std::vector<bool> visited(101, false);
        
        if(!findPath(fromEq, toEq, path, visited)) {
            printf("\n  No path found from %d to %d", fromEq, toEq);
            return false;
        }
        
        printf("\n  Path: ");
        for(size_t i = 0; i < path.size(); i++) {
            printf("%d", path[i]);
            if(i < path.size() - 1) printf(" -> ");
        }
        
        // Execute equations in path order
        bool allPassed = true;
        for(int eqNum : path) {
            Equation* eq = m_executor.getEquation(eqNum);
            if(eq) {
                TestResult result = testEquation(*eq, m_testContext);
                if(!result.passed) {
                    allPassed = false;
                }
            }
        }
        
        return allPassed;
    }
    
    // Validate result accuracy
    bool validateResultAccuracy(int eqNum, const float* expected,
                                size_t size, float tolerance = 1e-5f) {
        Equation* eq = m_executor.getEquation(eqNum);
        if(!eq) {
            printf("\n[Accuracy Test] Eq %d not found", eqNum);
            return false;
        }
        
        const EquationData& output = m_testContext.getOutput(eqNum);
        
        if(output.size != size) {
            printf("\n[Accuracy Test] Eq %d: size mismatch (expected %d, got %d)",
                   eqNum, (int)size, (int)output.size);
            return false;
        }
        
        float maxError = 0.0f;
        for(size_t i = 0; i < size; i++) {
            float error = fabsf(output.values[i] - expected[i]);
            if(error > maxError) maxError = error;
            
            if(error > tolerance) {
                printf("\n[Accuracy Test] Eq %d: value[%d] error %.6f (tol %.6f)",
                       eqNum, (int)i, error, tolerance);
                return false;
            }
        }
        
        printf("\n[Accuracy Test] Eq %d: PASS (max error %.6f)", eqNum, maxError);
        return true;
    }
    
    // Print test report
    void printTestReport() const {
        printf("\n\n========================================");
        printf("\n           TEST REPORT");
        printf("\n========================================");
        printf("\n Total Equations:    %d", m_totalTests);
        printf("\n Passed:             %d (%.1f%%)",
               m_passedTests, 100.0f * m_passedTests / (m_totalTests + 0.001f));
        printf("\n Failed:             %d", m_failedTests);
        
        if(m_failedTests > 0) {
            printf("\n\n Failed Tests:");
            for(const auto& result : m_testResults) {
                if(!result.passed) {
                    printf("\n  Eq %d (%s): %s",
                           result.equationNumber,
                           result.equationTitle ? result.equationTitle : "Unknown",
                           result.errorMessage ? result.errorMessage : "Unknown error");
                }
            }
        }
        
        // Print slowest equations
        printf("\n\n Slowest Equations:");
        std::vector<const TestResult*> sorted;
        for(const auto& r : m_testResults) {
            sorted.push_back(&r);
        }
        std::sort(sorted.begin(), sorted.end(),
                  [](const TestResult* a, const TestResult* b) {
                      return a->executionTimeMs > b->executionTimeMs;
                  });
        
        int showCount = (sorted.size() < 10) ? sorted.size() : 10;
        for(int i = 0; i < showCount; i++) {
            printf("\n  %d. Eq %d: %.3f ms",
                   i+1, sorted[i]->equationNumber, sorted[i]->executionTimeMs);
        }
        
        printf("\n========================================\n");
    }
    
    // Get context for inspection
    EquationContext& getContext() { return m_testContext; }
    
private:
    double getTimestamp() {
        // Simple timestamp using clock()
        return (double)clock() / (double)CLOCKS_PER_SEC;
    }
    
    bool findPath(int from, int to, std::vector<int>& path,
                  std::vector<bool>& visited) {
        if(from == to) {
            path.push_back(from);
            return true;
        }
        
        visited[from] = true;
        path.push_back(from);
        
        Equation* eq = m_executor.getEquation(from);
        if(eq) {
            for(int i = 0; i < eq->getNumDownstream(); i++) {
                int next = eq->getDownstreamDep(i);
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
};

}  // namespace EquationSystem

#endif
