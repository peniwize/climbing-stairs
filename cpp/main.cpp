/*!
    \file "main.cpp"

    Author: Matt Ervin <matt@impsoftware.org>
    Formatting: 4 spaces/tab (spaces only; no tabs), 120 columns.
    Doc-tool: Doxygen (http://www.doxygen.com/)

    https://leetcode.com/problems/climbing-stairs/
*/

//!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/main.md
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h> //!\sa https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
#include <iomanip>

using namespace std;

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

class Solution {
public:
    /*
        01: 0 1 2 3 4
            a

        02: 0_1 2 3 4 # First way to arrange 2..4; how many additional ways to arrange?
              a b
        03: 0_1 2_3 4
              a   b c 
        04: 0_1 2 3_4
              a     b

        05: 0 1_2 3 4 # First way to arrange 0, 3..4; how many additional ways to arrange?
                a b
        06: 0 1_2 3_4
                a   b

        07: 0 1 2_3 4 # First way to arrange 0..1, 4; how many additional ways to arrange?
                  a b

        08: 0 1 2 3_4 # First way to arrange 0..2; how many additional ways to arrange?
                    a

        Combine(array, i=0):
            if 2 < len(array) && len(array) - 2 > i:
                Combine the first pair in the array.
                Combine(arrayp[i,])
    */
    int climbStairs(int n) {
        if (0 == n) { return 0; }
        
        int count = 1;        
        for (int i = 1; n > i; ++i) { // 'i' addresses the right-most item in the pair.
            auto const remaining_items = n - i - 1;
            if (0 < remaining_items) {
                count += climbStairs(remaining_items);
            } else {
                ++count;
            }
        }

        return count;
    }

    /*
        Combine(array, i=0):
            if 2 < len(array) && len(array) - 2 > i:
                Combine the first pair in the array.
                Combine(arrayp[i,])
    */
    int climbStairsWithLogging(int n, int const prev_i = -1) {
        if (0 == n) { return 0; }
        
        // First sequence is always discrete uncombined steps, e.g [0 1 2 3 4]
        auto const is_top_level_call = -1 == prev_i;
        int const sub_seq_idx = prev_i + 1;
        int line_number = prev_i + 2;
        int count = 1;

        // Print remainder of combination.
        if (is_top_level_call) {
            cerr << dec << setw(2) << line_number << ": ";
        }
        for (int j = 0; n > j; ++j) {
            if (0 < j) { cerr << ' '; }
            cerr << dec << (sub_seq_idx + j);
        }
        cerr << '\n';
        ++line_number;
        
        for (int i = 1; n > i; ++i) { // 'i' addresses the right-most item in the pair.
            // Print line number.
            if (is_top_level_call) {
                cerr << dec << setw(2) << (line_number) << ": ";
            } else {
                cerr << "    ";
            }
            // Print prefix gap.
            for (int j = 0; sub_seq_idx > j; ++j) {
                cerr << '.' << '.';
            }
            // Print first part of new combination.
            for (int j = 0; i > j; ++j) {
                if (0 < j) { cerr << ' '; }
                cerr << dec << (sub_seq_idx + j);
            }
            cerr << '_' << dec << (sub_seq_idx + i) << ' ';
            
            auto const old_count = count;
            
            auto const remaining_items = n - i - 1;
            if (0 < remaining_items) {
                count += climbStairsWithLogging(remaining_items, sub_seq_idx + i);
            } else {
                ++count;
                cerr << '\n';
            }

            line_number += count - old_count;
        }

        return count;
    }
};

// [----------------(120 columns)---------------> Module Code Delimiter <---------------(120 columns)----------------]

TEST_CASE("Case 0")
{
    auto solution = Solution{};
    cerr << "Case 0" << '\n';
    CHECK(0 == solution.climbStairs(0));
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

/*
    End of "main.cpp"
*/
