#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

bool isCrossed(const pair<int, pair<int, int>>& firstPlus, const pair<int, pair<int, int>>& secondPlus)
{
    auto firstBranch = (firstPlus.first - 1) / 4;
    auto secondBranch = (secondPlus.first - 1) / 4;

    if (firstPlus.second.first == secondPlus.second.first)
        return abs(firstPlus.second.second - secondPlus.second.second) <= firstBranch + secondBranch;

    if (firstPlus.second.second == secondPlus.second.second)
        return abs(firstPlus.second.first - secondPlus.second.first) <= firstBranch + secondBranch;

    if (abs(firstPlus.second.first - secondPlus.second.first) <= max(firstBranch, secondBranch)
         && abs(firstPlus.second.second - secondPlus.second.second) <= min(firstBranch, secondBranch))
        return true;

    if (abs(firstPlus.second.second - secondPlus.second.second) <= max(firstBranch, secondBranch)
        && abs(firstPlus.second.first - secondPlus.second.first) <= min(firstBranch, secondBranch))
        return true;
   
    return false;
}

// Complete the twoPluses function below.
int twoPluses(vector<string> grid) 
{
    if (grid.size() == 2 || grid[0].size() == 2)
    {
        for (const auto& row : grid)
            if (row.find('G') != string::npos)
                return 1;
        return 0;
    }

    vector<vector<int>> field;
    for (const auto& row : grid)
    {
        vector<int> fieldRow(row.length());
        transform(cbegin(row), cend(row),
            begin(fieldRow),
            [](const auto& c)
            {
                return (c == 'B') ? 0 : 1;
            }
        );
        field.push_back(fieldRow);
    }

    int productPlus = 0;

    for (const auto i : { (size_t)0, grid.size() - 1 })
    {
        for (const auto& cell : field[i])
        {
            if (cell == 1)
            {
                productPlus = 1;
                break;
            }
        }
        if (productPlus > 0) break;
    }

    multimap<int, pair<size_t, size_t>> pluses;
    for (size_t i = 1; i < field.size() - 1; ++i)
    {
        if (field[i][0] == 1 || field[i][field[i].size() - 1] == 1) productPlus = max(productPlus, 1);
        for (size_t j = 1; j < field[i].size() - 1; ++j)
        {
            if (field[i][j] == 1)
            {
                int upBranch = 0;
                for (int k = i - 1; k >= 0; --k)
                {
                    if (field[k][j] == 1)
                        ++upBranch;
                    else
                        break;
                }
                if (upBranch == 0)
                {
                    productPlus = max(productPlus, 1);
                    continue;
                }

                int downBranch = 0;
                for (size_t k = i + 1; k < field.size(); ++k)
                {
                    if (field[k][j] == 1)
                        ++downBranch;
                    else
                        break;
                }
                if (downBranch == 0) 
                {
                    productPlus = max(productPlus, 1);
                    continue;
                }

                int leftBranch = 0;
                for (int k = j - 1; k >= 0; --k)
                {
                    if (field[i][k] == 1)
                        ++leftBranch;
                    else
                        break;
                }
                if (leftBranch == 0) 
                {
                    productPlus = max(productPlus, 1);
                    continue;
                }

                int rightBranch = 0;
                for (size_t k = j + 1; k < field[i].size(); ++k)
                {
                    if (field[i][k] == 1)
                        ++rightBranch;
                    else
                        break;
                }
                if (rightBranch == 0) 
                {
                    productPlus = max(productPlus, 1);
                    continue;
                }

                auto shortestBranch = min({ upBranch, downBranch, leftBranch, rightBranch });

                for (int l = shortestBranch; l > 0; --l)
                {
                    auto plusSquare = l * 4 + 1;
                    pluses.insert({ plusSquare, { i, j } });
                }
            }
        }
    }

    int maxProduct = pluses.empty() ? productPlus : crbegin(pluses)->first;

    for (auto it = crbegin(pluses); it != crend(pluses); ++it)
    {
        for (auto jt = next(it); jt != crend(pluses); ++jt)
        {
            if (!isCrossed(*it, *jt))
            {
                if (maxProduct < (*it).first * (*jt).first)
                    maxProduct = (*it).first * (*jt).first;
            }
        }
    }

    return maxProduct;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
