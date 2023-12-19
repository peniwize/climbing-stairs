/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/climbing-stairs/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cassert>
#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iomanip>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

class Solution {
public:
    /*
        Problem:

        You are climbing a staircase. It takes n steps to reach the top.
        Each time you can either climb 1 or 2 steps.
        In how many distinct ways can you climb to the top?
        
        Solution:
        
        Find every combination of ways of taking steps.
        Every valid combination will end on exactly the last step.
        Count the number of ways the last step is reached.
        This is the answer.

        Example 1 (two steps):

                +---+
                | 2 |
            +---+
            | 1 |
        ----+
          0 (no step)

        There are two ways to advance from step 0:
            0 -> 1 (climb one step)
            There is one [valid] way to advance from step 1:
                1 -> 2 (climb one step)
                * There is no way to advance; top step reached.
                Taking two steps would overshoot step 2,
                which is an invalid outcome since there is no third step!
            0 -> 2 (climb two steps)
            * There is no way to advance; top step reached.

            The answer is the number of times step 2 was reached,
            denoted with '*', which is two.

            Decision trees are used to graph every combination in a solution set.
            Note that the explanation above create this [horizontal] decision tree:

                2
               /
              1
             / \
            0   x
             \
              2
            
            Each node in the tree represents a step on the staircase.
            Starting at the landing (0), there are two ways to advance: 
            chose one step or chose two steps.
            Chosing one step leads to node 1.
            Chosing two steps leads to node 2 (the final step).
            From node 1 there are two ways to advance: 
            chose one step or chose two steps.
            Chosing one step leads to node 2 (the final step).
            Chosing two steps leads to 'x' (an invalid outcome; because there is no third step).
            The final step (2) can be reached two ways.

        Patterns:

            Note: a skipped step is joind to the following step with '+'

            1 2 (take two steps)
            1+2 (take one step)

        Example 2 (four steps):

                        +---+
                        | 4 |
                    +---+
                    | 3 |
                +---+
                | 2 |
            +---+
            | 1 |
        ----+
          0 (no step)
        
        There are two ways to advance from step 0:
            0 -> 1 (climb one step)
            There are two ways to advance from step 1:
                1 -> 2 (climb one step)
                There are two ways to advance from step 2:
                    2 -> 3 (climb one step)
                    There is one way to advance from step 3:
                        3 -> 4 (climb one step)
                        * There is no way to advance; top step reached.
                    2 -> 4 (climb two steps)
                    * There is no way to advance; top step reached.
                1 -> 3 (climb two steps)
                There is one way to advance from step 3:
                    3 -> 4 (climb one step)
                    * There is no way to advance; top step reached.
            0 -> 2 (climb two steps)
            There are two ways to advance from step 2:
                2 -> 3 (climb one step)
                There is one way to advance from step 3:
                    3 -> 4 (climb one step)
                    * There is no way to advance; top step reached.
                2 -> 4 (climb two steps)
                * There is no way to advance; top step reached.

            The answer is the number of times step 4 was reached,
            denoted with '*', which is five.

            The [vertical] decision tree for the explanation above is:
            Note: the decision tree could also be horizontal.

                            0
                     /             \
                    1               2
                 /     \         /     \
                2       3       3       4
               / \     / \     / \
              3   4   4   x   4   x
             / \
            4   x
            
            Branches that end with 'x' are invalid combinations, 
            which do not produce a valid result, and are therefore uncounted.
            The final step (4) can be reached five ways.

        Patterns:

            Note: a skipped step is joind to the following step with '+'

            1 2 3 4
            1+2 3 4
            1+2 3+4
            1 2+3 4
            1 2 3+4
    
        The examples above show how all combinations of all ways of taking
        a step are produced.

        Time = O(2^n) == number of decision tree nodes visited.
        Space = O(n) == number of levels of recursion.
    */
    int climbStairs_BruteForce_Recursive(int const n, int currentStep) {
        if (n == currentStep) {
            return 1;
        } else if (n < currentStep) {
            return 0; // Invalid branch/outcome; went beyone final step.
        }
        
        // Advance from node in the decision tree by taking either:
        return climbStairs_BruteForce_Recursive(n, currentStep + 1)    // one step
               + climbStairs_BruteForce_Recursive(n, currentStep + 2); // or two steps.
        // Only choices that ultimately lead to the final step 
        // will produce a value > 0.  The result of each choice is 
        // summed because all banches in the decision tree must be
        // fully explored.
    }

    int climbStairs_BruteForce(int const n) {
        return climbStairs_BruteForce_Recursive(n, 0);
    }

    /*!
        This implementation is similar to 
        'climbStairs_BruteForce_Recursive(int const n, int currentStep)',
        except that it eliminates the 'currentStep' parameter by traveling
        DOWN the steps to the landing rather than traveling UP the steps to
        the stop step.

        Time = O(2^n) == number of decision tree nodes visited.
        Space = O(n) == number of levels of recursion.
    */
    int climbStairs_Backward_BruteForce_Recursive(int const n) {
        if (0 == n) {
            return 1;
        } else if (0 > n) {
            return 0; // Invalid branch/outcome; went beyone final step.
        }
        
        // Advance from node in the decision tree by taking either:
        return climbStairs_Backward_BruteForce_Recursive(n - 1)    // one step
               + climbStairs_Backward_BruteForce_Recursive(n - 2); // or two steps.
        // Only choices that ultimately lead to the final step 
        // will produce a value > 0.  The result of each choice is 
        // summed because all banches in the decision tree must be
        // fully explored.
    }

    /*!
        This implementation is similar to 
        'climbStairs_Backward_BruteForce_Recursive(int const n)',
        except that it uses memoization to aviod redundantly reevaluating 
        steps (nodes in the decision tree) that were previously evaluated.

        Time = O(2n) => O(n) == number of decision tree levels.
        Space = O(O(n) + O(n+1)) => O(2n) => O(n) ==
                number of [decision tree] levels of recursion + cache size.
    */
    int climbStairs_Backward_Memoized_Recursive(int const n, int cache[]) {
        int result = -1;
        
        if (0 == n) {
            result = 1;
        } else if (0 > n) {
            result = 0; // Invalid branch/outcome; went beyone final step.
        } else if (-1 != cache[n]) {
            result = cache[n];
        } else {
            // Advance from node in the decision tree by taking either:
            result = climbStairs_Backward_Memoized_Recursive(n - 1, cache)   // one step
                    + climbStairs_Backward_Memoized_Recursive(n - 2, cache); // or two steps.
            // Only choices that ultimately lead to the final step 
            // will produce a value > 0.  The result of each choice is 
            // summed because all banches in the decision tree must be
            // fully explored.
            
            assert(-1 == cache[n] || result == cache[n]);
            cache[n] = result;
        }

        return result;
    }

    int climbStairs_Backward_Memoized(int const n) {
        int cache[n + 1];
        std::fill_n(cache, n + 1, -1);
        return climbStairs_Backward_Memoized_Recursive(n, cache);
    }

    /*!
        This implementation is similar to:
        'climbStairs_Backward_Memoized(int const n)',
        except that it emliminates the need for a cache array.
        This implementation also climbs the stairs forward and 
        is exactly how Fibonacci numbers are calculated.

        Time = O(n-2) => O(n)
        Space = O(1)
    */
    int climbStairs_Optimized(int n) {
        if (0 > n) {
            return 0;
        } else if (2 > n) {
            return 1;
        }

        int n_minus_two = 1; // Initial value for the second step.
        int n_minus_one = 1; // Initial value for the second step.
        int result = 2;
        --n; // Initial values assume first two steps taken.
        --n; // Initial values assume first two steps taken.
        while (0 < n--) {
            n_minus_two = n_minus_one;
            n_minus_one = result;
            result = n_minus_one + n_minus_two;
        }
        return result;
    }

    int climbStairs(int n) {
        return climbStairs_Optimized(n);
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 0")
{
    auto solution = Solution{};
    cerr << "Case 0" << '\n';
    CHECK(1 == solution.climbStairs(0));
    cerr << '\n';
}

TEST_CASE("Case 1")
{
    auto solution = Solution{};
    cerr << "Case 1" << '\n';
    CHECK(1 == solution.climbStairs(1));
    cerr << '\n';
}

TEST_CASE("Case 2")
{
    auto solution = Solution{};
    cerr << "Case 2" << '\n';
    CHECK(2 == solution.climbStairs(2));
    cerr << '\n';
}

TEST_CASE("Case 3")
{
    auto solution = Solution{};
    cerr << "Case 3" << '\n';
    CHECK(3 == solution.climbStairs(3));
    cerr << '\n';
}

TEST_CASE("Case 4")
{
    auto solution = Solution{};
    cerr << "Case 4" << '\n';
    CHECK(5 == solution.climbStairs(4));
    cerr << '\n';
}

TEST_CASE("Case 5")
{
    auto solution = Solution{};
    cerr << "Case 5" << '\n';
    CHECK(8 == solution.climbStairs(5));
    cerr << '\n';
}

TEST_CASE("Case 45")
{
    auto solution = Solution{};
    cerr << "Case 45" << '\n';
    CHECK(1836311903 == solution.climbStairs(45));
    cerr << '\n';
}

/*
    End of "main.cpp"
*/
