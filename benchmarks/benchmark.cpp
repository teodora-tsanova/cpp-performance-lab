
#include "frequency_queries.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: benchmark <original|optimized>\n";
        return 1;
    }

    int q;
    if (!(std::cin >> q) || q < 0) {
        std::cerr << "Invalid number of queries\n";
        return 1;
    }

    std::vector<std::vector<int>> queries(q);

    for (int i = 0; i < q; ++i) {
        int operation;
        int value;

        if (!(std::cin >> operation >> value)) {
            std::cerr << "Invalid query input\n";
            return 1;
        }

        queries[i] = {operation, value};
    }

    std::vector<int> result;

    const std::string algorithm = argv[1];

    if (algorithm == "original") {
        result = freqQuery(queries);
    } else if (algorithm == "optimized") {
        result = freqQueryOptimized(queries);
    } else {
        std::cerr << "Unknown algorithm: " << algorithm << '\n';
        return 1;
    }

    // Calculate a checksum instead of printing every result.
    std::uint64_t checksum = 0;

    for (int value : result) {
        checksum += value;
    }

    std::cout << "Checksum: " << checksum << '\n';

    return 0;
}
