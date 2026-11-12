#include "frequency_queries.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int q;
    cin >> q;

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        int operation, value;
        cin >> operation >> value;
        queries[i] = {operation, value};
    }


    //auto result = freqQuery(queries);
    //auto optimizedResult = freqQueryOptimized(queries);

    //if (result != optimizedResult) {
    //    cerr << "Algorithms produced different results!\n";
    //    return 1;
    //}
    auto result = freqQuery(queries);

    for (int value : result) {
        cout << value << '\n';
    }

    return 0;
}