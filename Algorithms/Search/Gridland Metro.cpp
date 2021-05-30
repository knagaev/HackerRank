#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'gridlandMetro' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. INTEGER k
 *  4. 2D_INTEGER_ARRAY track
 */

long long gridlandMetro(long n, long m, long k, vector<vector<long>> track) 
{
    sort(begin(track), end(track),
        [](const auto& lhs, const auto& rhs)
        {
            return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
        }
    );

    long long used = 0;
    long curRow = 1;
    long startCell = 0, finishCell = -1;
    for (const auto& t : track)
    {
        if (curRow != t[0])
        {
            used += finishCell - startCell + 1;
            curRow = t[0];
            startCell = t[1];
            finishCell = t[2];
        }
        else
        {
            if (t[1] > finishCell)
            {
                used += finishCell - startCell + 1;
                startCell = t[1];
                finishCell = t[2];
            }
            else
            {
                finishCell = max(finishCell, t[2]);
            }
        }
    }
    used += finishCell - startCell + 1;

    return (long long)n * m - used;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    long n = stol(first_multiple_input[0]);

    long m = stol(first_multiple_input[1]);

    long k = stol(first_multiple_input[2]);

    vector<vector<long>> track(k);

    for (long i = 0; i < k; i++) {
        track[i].resize(3);

        string track_row_temp_temp;
        getline(cin, track_row_temp_temp);

        vector<string> track_row_temp = split(rtrim(track_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            long track_row_item = stol(track_row_temp[j]);

            track[i][j] = track_row_item;
        }
    }

    long result = gridlandMetro(n, m, k, track);

    fout << result << "\n";

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
