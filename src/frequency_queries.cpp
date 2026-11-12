#include "frequency_queries.h"
#include <unordered_map>

using namespace std;

vector<int> freqQuery(const vector<vector<int>>& queries) {
    unordered_map<int,int> numToFreq;
    vector<int> ret;
    
    for(const auto& elem: queries){
        if (elem[0] == 1){
            numToFreq[elem[1]]++;
        }else if(elem[0] == 2) {
            if (numToFreq[elem[1]])
                numToFreq[elem[1]]--;
        }else if(elem[0] == 3) {
            bool found = false;
            for(auto [num, freq]:numToFreq) 
                if (freq == elem[1]){
                    found = true;
                    break;
                }     
            ret.push_back(int(found));  
        }
    }
    return ret;
}

vector<int> freqQueryOptimized(const vector<vector<int>>& queries) {
    std::unordered_map<int, int> numToFreq;
    std::unordered_map<int, int> freqToCount;

    std::vector<int> ret;

    for (const auto& elem : queries) {
        int operation = elem[0];
        int value = elem[1];

        if (operation == 1) {
            int oldFreq = numToFreq[value];
            int newFreq = oldFreq + 1;

            if (oldFreq > 0) {
                freqToCount[oldFreq]--;
            }

            numToFreq[value] = newFreq;
            freqToCount[newFreq]++;

        } else if (operation == 2) {
            int oldFreq = numToFreq[value];

            if (oldFreq > 0) {
                int newFreq = oldFreq - 1;

                freqToCount[oldFreq]--;

                numToFreq[value] = newFreq;

                if (newFreq > 0) {
                    freqToCount[newFreq]++;
                }
            }

        } else if (operation == 3) {
            ret.push_back(freqToCount[value] > 0 ? 1 : 0);
        }
    }

    return ret;
}