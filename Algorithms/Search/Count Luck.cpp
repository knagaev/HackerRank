#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct State
{
    int row;
    int col;
    int wavesUsed;
};

string countLuck(vector<string> matrix, int k) 
{
    int rowStart = -1, colStart = -1;

    for (auto it = begin(matrix); rowStart < 0 && it != end(matrix); ++it)
    {
        for (auto jt = begin(*it); colStart < 0 && jt != end(*it); ++jt)
        {
            if (*jt == 'M')
            {
                rowStart = distance(begin(matrix), it);
                colStart = distance(begin(*it), jt);
            }
        }
    }

    deque<State> q{ State{rowStart, colStart, 0} };
    while (!q.empty())
    {
        auto curPoint = q.front();
        q.pop_front();
        
        vector<State> nextSteps;
        bool finalStep = false;
        for (auto i : { -1, 0, 1 })
        {
            auto nextRow = curPoint.row + i;
            if (nextRow < 0 || nextRow >= matrix.size()) continue;
            for (auto j : { -1, 0, 1 })
            {
                if (abs(i + j) != 1) continue;

                auto nextCol = curPoint.col + j;
                if (nextCol < 0 || nextCol >= matrix[nextRow].size()) continue;
                
                if (matrix[nextRow][nextCol] == '*')
                {
                    nextSteps.push_back(State{ nextRow, nextCol, curPoint.wavesUsed + 1});
                    finalStep = true;
                }
                if (matrix[nextRow][nextCol] == '.')
                {
                    nextSteps.push_back(State{ nextRow, nextCol, curPoint.wavesUsed + 1 });
                    matrix[nextRow][nextCol] = 'P';
                }
            }
        }
        if (finalStep)
        {
            return (((curPoint.wavesUsed + ((nextSteps.size() > 1) ?
                1 :
                0))) != k) ? 
                "Oops!" : 
                "Impressed";
        }

        if (nextSteps.size() == 1)
            q.push_back(State{ nextSteps[0].row, nextSteps[0].col, curPoint.wavesUsed });
        else
            q.insert(end(q), begin(nextSteps), end(nextSteps));
    }

    return "Oops!";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        string k_temp;
        getline(cin, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));

        string result = countLuck(matrix, k);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
