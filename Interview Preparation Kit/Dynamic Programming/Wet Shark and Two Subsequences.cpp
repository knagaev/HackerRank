#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the twoSubsequences function below.
 */
int twoSubsequences(vector<int> x, int r, int s) 
{
    const long long modulus = 1e9 + 7;

    if (s > r) 
        return 0;
    
    if ((r + s) % 2 != 0 || (r - s) % 2 != 0) 
        return 0;
    
    auto k = (r + s) / 2;
    
    vector<vector<long long>> arr(k + 1, vector<long long>(x.size() + 1));
    
    arr[0][0] = 1;
    
    for (int i = x.size() - 1; i >= 0; --i)
    {
        for (int j = k; j >= 0; --j)
        {
            for (int z = x.size(); z >= 1; --z)
            {
                auto op1 = 0;
                if (j >= x[i]) 
                    op1 = arr[j - x[i]][z - 1] % modulus;

                auto op2 = arr[j][z] % modulus;
                arr[j][z] = ((op1 % modulus) + (op2 % modulus)) % modulus;
            }
        }
    }
    auto result { 0LL };
    auto q { 0LL }, w { 0LL }, t { 0LL }, t2 { 0LL };

    for (size_t i = 1; i <= x.size(); ++i)
    {
        q = arr[(r + s) / 2][i] % modulus;
        w = arr[(r - s) / 2][i] % modulus;

        if (q == 0 || w == 0) continue;
        
        if (s != 0)
        {
            t = ((q % modulus) * (w % modulus)) % modulus;
            result = ((result % modulus) + (t % modulus)) % modulus;
        }
        else if (s == 0)
        {
            t = ((q % modulus) * (q % modulus)) % modulus;
            result = ((result % modulus) + (t % modulus)) % modulus;
        }
    }
    return result % modulus;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string mrs_temp;
    getline(cin, mrs_temp);

    vector<string> mrs = split_string(mrs_temp);

    int m = stoi(mrs[0]);

    int r = stoi(mrs[1]);

    int s = stoi(mrs[2]);

    string x_temp_temp;
    getline(cin, x_temp_temp);

    vector<string> x_temp = split_string(x_temp_temp);

    vector<int> x(m);

    for (int x_itr = 0; x_itr < m; x_itr++) {
        int x_item = stoi(x_temp[x_itr]);

        x[x_itr] = x_item;
    }

    int result = twoSubsequences(x, r, s);

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
