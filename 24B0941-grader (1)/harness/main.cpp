// ----------------------------------------------------------------
// DO NOT UPDATE ANYTHING IN THIS FILE
// ----------------------------------------------------------------
#include <iostream>
#include <vector>
#include "max-fish.h"
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
    if (argc > 1) {
        if (freopen(argv[1], "r", stdin) == nullptr) // cin redirects to file argv[1]
        {
            std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
            return 1;
        }
    }
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> grid[i][j];
        }
    }

    Solution solution;

    
    int result;
    long long total_time = 0;
    for (int i = 0; i < 10; ++i ) {
        auto start = std::chrono::system_clock::now();
        result = solution.findMaxFish(grid);
        auto elapsed = std::chrono::system_clock::now()- start;
        total_time += elapsed.count();
    }
    cout << "Result:" << result << '\n';
    std::cout << "Time:" << total_time << '\n';

    return 0;
}
