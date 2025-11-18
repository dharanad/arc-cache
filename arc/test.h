#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <optional>
#include <string>
#include <sstream>

// Color codes for terminal output
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"

// Test statistics
namespace TestStats {
    static int total_tests = 0;
    static int passed_tests = 0;
    static int failed_tests = 0;
}

// Helper macro to print file and line info
#define TEST_LOCATION __FILE__ << ":" << __LINE__

// Basic assertion - evaluates condition
#define ASSERT(condition) \
    do { \
        TestStats::total_tests++; \
        if (condition) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " << #condition << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " << #condition << std::endl; \
        } \
    } while(0)

// Assert with custom message
#define ASSERT_MSG(condition, message) \
    do { \
        TestStats::total_tests++; \
        if (condition) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " << message << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " << message << std::endl; \
        } \
    } while(0)

// Assert equality for integers
#define ASSERT_EQ(expected, actual) \
    do { \
        TestStats::total_tests++; \
        auto exp_val = (expected); \
        auto act_val = (actual); \
        if (exp_val == act_val) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " == " << #expected << " (" << act_val << ")" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " == " << #expected << std::endl \
                      << "  Expected: " << exp_val << std::endl \
                      << "  Actual:   " << act_val << std::endl; \
        } \
    } while(0)

// Assert inequality
#define ASSERT_NE(not_expected, actual) \
    do { \
        TestStats::total_tests++; \
        auto nexp_val = (not_expected); \
        auto act_val = (actual); \
        if (nexp_val != act_val) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " != " << #not_expected << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " != " << #not_expected << std::endl \
                      << "  Both values are: " << act_val << std::endl; \
        } \
    } while(0)

// Assert string equality
#define ASSERT_STR_EQ(expected, actual) \
    do { \
        TestStats::total_tests++; \
        std::string exp_str = (expected); \
        std::string act_str = (actual); \
        if (exp_str == act_str) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " == " << #expected << " (\"" << act_str << "\")" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #actual << " == " << #expected << std::endl \
                      << "  Expected: \"" << exp_str << "\"" << std::endl \
                      << "  Actual:   \"" << act_str << "\"" << std::endl; \
        } \
    } while(0)

// Assert optional has value
#define ASSERT_HAS_VALUE(optional_val) \
    do { \
        TestStats::total_tests++; \
        auto opt = (optional_val); \
        if (opt.has_value()) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " has value (" << opt.value() << ")" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " has no value (expected to have value)" << std::endl; \
        } \
    } while(0)

// Assert optional has no value
#define ASSERT_NO_VALUE(optional_val) \
    do { \
        TestStats::total_tests++; \
        auto opt = (optional_val); \
        if (!opt.has_value()) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " has no value" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " has value (" << opt.value() << "), expected no value" << std::endl; \
        } \
    } while(0)

// Assert optional value equals expected
#define ASSERT_OPTIONAL_EQ(expected, optional_val) \
    do { \
        TestStats::total_tests++; \
        auto exp_val = (expected); \
        auto opt = (optional_val); \
        if (opt.has_value() && opt.value() == exp_val) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " == " << #expected << " (" << exp_val << ")" << std::endl; \
        } else if (!opt.has_value()) { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " has no value, expected " << exp_val << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #optional_val << " == " << #expected << std::endl \
                      << "  Expected: " << exp_val << std::endl \
                      << "  Actual:   " << opt.value() << std::endl; \
        } \
    } while(0)

// Assert true
#define ASSERT_TRUE(condition) \
    do { \
        TestStats::total_tests++; \
        if (condition) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #condition << " is true" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #condition << " is false (expected true)" << std::endl; \
        } \
    } while(0)

// Assert false
#define ASSERT_FALSE(condition) \
    do { \
        TestStats::total_tests++; \
        if (!(condition)) { \
            TestStats::passed_tests++; \
            std::cout << COLOR_GREEN << "[PASS] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #condition << " is false" << std::endl; \
        } else { \
            TestStats::failed_tests++; \
            std::cerr << COLOR_RED << "[FAIL] " << COLOR_RESET << TEST_LOCATION << ": " \
                      << #condition << " is true (expected false)" << std::endl; \
        } \
    } while(0)

// Comparison assertions
#define ASSERT_GT(actual, threshold) ASSERT_MSG((actual) > (threshold), #actual " > " #threshold)
#define ASSERT_GE(actual, threshold) ASSERT_MSG((actual) >= (threshold), #actual " >= " #threshold)
#define ASSERT_LT(actual, threshold) ASSERT_MSG((actual) < (threshold), #actual " < " #threshold)
#define ASSERT_LE(actual, threshold) ASSERT_MSG((actual) <= (threshold), #actual " <= " #threshold)

// Debugging macros
#define DEBUG_PRINT(var) \
    std::cout << COLOR_CYAN << "[DEBUG] " << COLOR_RESET << TEST_LOCATION << ": " \
              << #var << " = " << (var) << std::endl

#define DEBUG_MSG(message) \
    std::cout << COLOR_CYAN << "[DEBUG] " << COLOR_RESET << TEST_LOCATION << ": " \
              << message << std::endl

// Test section markers
#define TEST_SECTION(name) \
    std::cout << std::endl << COLOR_YELLOW << "=== " << name << " ===" << COLOR_RESET << std::endl

#define TEST_SUBSECTION(name) \
    std::cout << COLOR_MAGENTA << "--- " << name << " ---" << COLOR_RESET << std::endl

// Print test summary
#define PRINT_TEST_SUMMARY() \
    do { \
        std::cout << std::endl << COLOR_YELLOW << "=== TEST SUMMARY ===" << COLOR_RESET << std::endl; \
        std::cout << "Total:  " << TestStats::total_tests << std::endl; \
        std::cout << COLOR_GREEN << "Passed: " << TestStats::passed_tests << COLOR_RESET << std::endl; \
        std::cout << COLOR_RED << "Failed: " << TestStats::failed_tests << COLOR_RESET << std::endl; \
        if (TestStats::failed_tests == 0) { \
            std::cout << COLOR_GREEN << "All tests passed!" << COLOR_RESET << std::endl; \
        } \
    } while(0)

// Reset test statistics
#define RESET_TEST_STATS() \
    do { \
        TestStats::total_tests = 0; \
        TestStats::passed_tests = 0; \
        TestStats::failed_tests = 0; \
    } while(0)

#endif // TEST_H
