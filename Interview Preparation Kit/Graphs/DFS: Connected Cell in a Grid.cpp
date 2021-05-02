#include <bits/stdc++.h>

using namespace std;

int dfsArea(size_t a, size_t b, vector<vector<int>>& grid)
{
    int area = 1;
    grid[a][b] = 0;

    for (int i = -1; i < 2; ++i)
    {
        if (a + i < 0 || a + i >= grid.size()) continue;
        for (int j = -1; j < 2; ++j)
        {
            if (b + j < 0 || b + j >= grid[a].size() || (i == 0 && j == 0)) continue;
            if (grid[a + i][b + j] == 1)
            {
                area += dfsArea(a + i, b + j, grid);
            }
        }
    }

    return area;
}

// Complete the maxRegion function below.
int maxRegion(vector<vector<int>> grid) 
{
    int maxArea = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid.size(); ++j)
        {
            if (grid[i][j] == 1)
                maxArea = max(maxArea, dfsArea(i, j, grid));
        }
    }
    return maxArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int m;
    cin >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<int>> grid(n);
    for (int i = 0; i < n; i++) {
        grid[i].resize(m);

        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int res = maxRegion(grid);

    fout << res << "\n";

    fout.close();

    return 0;
}
