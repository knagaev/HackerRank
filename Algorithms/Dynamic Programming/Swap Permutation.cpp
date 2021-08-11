#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'swapPermutation' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 */

const int maxN = 2500;
const long long modulo = 1000000007;

void update(vector<long long>& fenwick, int x, long long v)
{
    while (x <= maxN + 1)
    {
        fenwick[x] = (fenwick[x] + v) % modulo;
        x += x & -x;
    }
}

void addToRange(vector<long long>& fenwick, int l, int r, long long v)
{
    ++l;
    ++r;
    
    update(fenwick, l, v);
    update(fenwick, r + 1, -v);
}

long long get(const vector<long long>& fenwick, int x)
{
    x++;
    long long ret = 0;
    while (x > 0)
    {
        ret = (ret + fenwick[x]) % modulo;
        x -= x & -x;
    }
    return ret;
}

vector<long long> swapPermutation(int n, int k)
{
    vector<long long> fenwick(maxN + 5);

    // Amount of permutations of length i with j inversions
    vector<vector<long long>> permInversions(maxN + 5, vector<long long>(maxN + 5, 0LL));

    // Amount of permutations of length i with j cycles
    vector<vector<long long>> permCycles(maxN + 5, vector<long long>(maxN + 5, 0LL));


    permInversions[1][0] = 1;
    for (int i = 1; i < maxN; ++i)
    {
        for (int j = 0; j < maxN + 1; ++j)
            addToRange(fenwick, j, min(j + i, maxN), permInversions[i][j]);

        for (int j = 0; j < maxN + 1; ++j)
            permInversions[i + 1][j] = get(fenwick, j);

        for (int j = 0; j < maxN + 2; ++j)
            fenwick[j] = 0;
    }

    permCycles[1][1] = 1;
    for (int i = 1; i < maxN; ++i)
    {
        for (int j = 1; j < i + 1; ++j)
        {
            permCycles[i + 1][j + 1] = (permCycles[i + 1][j + 1] + permCycles[i][j]) % modulo;
            permCycles[i + 1][j] = (permCycles[i + 1][j] + permCycles[i][j] * i) % modulo;
        }
    }

    vector<long long> result(2);
    for (int j = k; j >= 0; j -= 2) 
        result[0] += permInversions[n][j];


    for (int i = 0; i < min(k + 1, n); ++i)
        result[1] += permCycles[n][n - i];

    result[0] %= modulo;
    result[1] %= modulo;

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    vector<long long> result = swapPermutation(n, k);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
