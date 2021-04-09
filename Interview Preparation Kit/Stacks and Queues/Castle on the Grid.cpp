#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumMoves function below.
int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) 
{
    set<vector<int>> allVisited { {startX, startY} };
    set<vector<int>> curVisited {allVisited};
    queue<vector<int>> curPoints;
    curPoints.push({ startX, startY, 0 });

    int result = 0;
    while (true)
    {
        if (curPoints.empty()) return numeric_limits<int>::max();

        auto curPoint = curPoints.front();
        curPoints.pop();
        auto currentX = curPoint[0];
        auto currentY = curPoint[1];

        for (int i = currentY - 1; i > -1; --i)
        {
            if (currentX == goalX && i == goalY) 
                return curPoint[2] + 1;
            if (grid[currentX][i] == 'X') 
                break;
            if (grid[currentX][i] == '.' && allVisited.find({ currentX, i }) == end(allVisited))
            {
                curPoints.push({ currentX, i, curPoint[2] + 1 });
                curVisited.insert({ currentX, i });
            }
        }

        for (int i = currentY + 1; i < grid[currentY].size(); ++i)
        {
            if (currentX == goalX && i == goalY) 
                return curPoint[2] + 1;
            if (grid[currentX][i] == 'X') 
                break;
            if (grid[currentX][i] == '.' && allVisited.find({ currentX, i }) == end(allVisited))
            {
                curPoints.push({ currentX, i, curPoint[2] + 1 });
                curVisited.insert({ currentX, i });
            }
        }

        for (int i = currentX - 1; i > -1; --i)
        {
            if (i == goalX && currentY == goalY)
                return curPoint[2] + 1;
            if (grid[i][currentY] == 'X') 
                break;
            if (grid[i][currentY] == '.' && allVisited.find({ i, currentY }) == end(allVisited))
            {
                curPoints.push({ i, currentY, curPoint[2] + 1 });
                curVisited.insert({ i, currentY });
            }
        }

        for (int i = currentX + 1; i < grid.size(); ++i)
        {
            if (i == goalX && currentY == goalY)
                return curPoint[2] + 1;
            if (grid[i][currentY] == 'X')
                break;
            if (grid[i][currentY] == '.' && allVisited.find({ i, currentY }) == end(allVisited))
            {
                curPoints.push({ i, currentY, curPoint[2] + 1 });
                curVisited.insert({ i, currentY });
            }
        }
        allVisited.insert(cbegin(curVisited), cend(curVisited));
        curVisited.clear();
    }
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

    string startXStartY_temp;
    getline(cin, startXStartY_temp);

    vector<string> startXStartY = split_string(startXStartY_temp);

    int startX = stoi(startXStartY[0]);

    int startY = stoi(startXStartY[1]);

    int goalX = stoi(startXStartY[2]);

    int goalY = stoi(startXStartY[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

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
