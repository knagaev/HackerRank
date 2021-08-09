#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'candlesCounting' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. 2D_INTEGER_ARRAY candles
 */

int intPow(int exp, int base = 2)
{
    int result{ 1 };
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

const long modulo = 1000000007;
const int maxCandlesQty = 50001;

long candlesCounting(int k, vector<vector<int>> candles) 
{
    auto options = intPow(k); // no one, first, second, first and second, ..., all 

    vector<vector<long>> fenwickTree (maxCandlesQty, vector<long>(options));

    long result = 0;
    
    vector<long> qtyByOptions(options), combinationsByOptions(options);
    for (const auto& candle : candles)
    {
        auto height = candle[0];
        auto alignedHeight = height - 1;
        auto alignedColour = candle[1] - 1;

        fill(begin(qtyByOptions), end(qtyByOptions), 0);

        // cumulated sums with height < alignedHeight for all options
        while (alignedHeight > 0)
        {
            for (int j = 0; j < options; ++j)
                qtyByOptions[j] += fenwickTree[alignedHeight][j];

            alignedHeight -= (alignedHeight & -alignedHeight);
        }

        fill(begin(combinationsByOptions), end(combinationsByOptions), 0);
        combinationsByOptions[1 << alignedColour] = 1;

        // all options with alignedColour
        for (int j = 0; j < options; ++j)
            combinationsByOptions[j | (1 << alignedColour)] += qtyByOptions[j] % modulo;

        result += combinationsByOptions.back() % modulo;  // option with all colours

        // recalculate tree with new combinations
        while (height < maxCandlesQty)
        {
            for (int j = 0; j < options; ++j)
                fenwickTree[height][j] += combinationsByOptions[j];

            height += (height & -height);
        }
    }

    return result % modulo;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    vector<vector<int>> candles(n);

    for (int i = 0; i < n; i++) {
        candles[i].resize(2);

        string candles_row_temp_temp;
        getline(cin, candles_row_temp_temp);

        vector<string> candles_row_temp = split(rtrim(candles_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int candles_row_item = stoi(candles_row_temp[j]);

            candles[i][j] = candles_row_item;
        }
    }

    long result = candlesCounting(k, candles);

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
