#include "frequency_queries.h"
#include <gtest/gtest.h>

TEST(FrequencyQueriesTest, BasicOperations) {
    std::vector<std::vector<int>> queries = {
        {1, 5},
        {1, 5},
        {1, 7},
        {3, 2},
        {3, 1},
        {3, 3}
    };

    std::vector<int> expected = {1, 1, 0};

    EXPECT_EQ(freqQuery(queries), expected);
    EXPECT_EQ(freqQueryOptimized(queries), expected);
}

TEST(FrequencyQueriesTest, DeleteMissingNumber) {
    std::vector<std::vector<int>> queries = {
        {2, 5},
        {1, 5},
        {3, 1},
        {3, 2}
    };

    std::vector<int> expected = {1, 0};

    EXPECT_EQ(freqQuery(queries), expected);
    EXPECT_EQ(freqQueryOptimized(queries), expected);
}

TEST(FrequencyQueriesTest, FrequencyBecomesZero) {
    std::vector<std::vector<int>> queries = {
        {1, 5},
        {2, 5},
        {3, 1},
        {1, 7},
        {3, 1}
    };

    std::vector<int> expected = {0, 1};

    EXPECT_EQ(freqQuery(queries), expected);
    EXPECT_EQ(freqQueryOptimized(queries), expected);
}

TEST(FrequencyQueriesTest, MultipleNumbersShareFrequency) {
    std::vector<std::vector<int>> queries = {
        {1, 5},
        {1, 5},
        {1, 7},
        {1, 7},
        {2, 5},
        {3, 2},
        {3, 1}
    };

    std::vector<int> expected = {1, 1};

    EXPECT_EQ(freqQuery(queries), expected);
    EXPECT_EQ(freqQueryOptimized(queries), expected);
}