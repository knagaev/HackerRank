#include <bits/stdc++.h>

using namespace std;

// Complete the cavityMap function below.
vector<string> cavityMap(vector<string> grid) 
{
    if (grid.size() < 3) return grid;
    
    for (auto it = next(begin(grid)); it != prev(end(grid)); ++it)
    {
        auto& currentRow = *it;
        auto& prevRow = *prev(it);
        auto& nextRow = *next(it);

        for (size_t i = 1; i < currentRow.size() - 1; ++i)
        {
            if (currentRow[i] > currentRow[i - 1] &&
                currentRow[i] > currentRow[i + 1] &&
                currentRow[i] > prevRow[i] &&
                currentRow[i] > nextRow[i])
                currentRow[i] = 'X';
        }
    }
    return grid;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = cavityMap(grid);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
