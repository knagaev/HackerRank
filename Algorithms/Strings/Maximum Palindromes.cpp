#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'initialize' function below.
 *
 * The function accepts STRING s as parameter.
 */

const long long modulo = 1000000007LL;
vector<vector<long>> runningSum(26, vector<long>());
vector<long long> factorialMods;
vector<long long> modularMultiplicativeInverses;

long long bin_pow(long long base, long long exp, long long modulo)
{
    if (exp == 1)
    {
        return base;
    }

    if (exp % 2 == 0)
    {
        long long t = bin_pow(base, exp / 2, modulo);
        return t * t % modulo;
    }
    else
    {
        long long t = bin_pow(base, exp - 1, modulo);
        return t * base % modulo;
    }
}

// x^(-1) mod m = x^(m-2) mod m
long long inverse_element(long long x, long long modulo)
{
    return bin_pow(x, modulo - 2, modulo);
}

//(a / b) mod m
long long divide(long long a, long long b, long long modulo)
{
    return a * inverse_element(b, modulo) % modulo;
}

void initialize(string s)
{
    // This function is called once before all queries.

    long i = 0;
    for (const auto& ch : s)
        runningSum[ch - 'a'].push_back(++i);

    factorialMods.resize(s.length());
    modularMultiplicativeInverses.resize(s.length());
    factorialMods[0] = 1;
    modularMultiplicativeInverses[0] = 1;
    for (long i = 1; i < s.length(); ++i)
    {
        factorialMods[i] = (factorialMods[i - 1] * i) % modulo;
        modularMultiplicativeInverses[i] = inverse_element(factorialMods[i], modulo);
    }
}

/*
 * Complete the 'answerQuery' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */

long long answerQuery(int l, int r)
{
    if (r - l == 0) return 1;

    // Return the answer for this query modulo 1000000007.
    vector<long long> difference(26);

    for (int i = 0; i < 26; ++i)
    {
        long long right = distance(begin(runningSum[i]), upper_bound(begin(runningSum[i]), end(runningSum[i]), r));
        long long left = distance(begin(runningSum[i]), lower_bound(begin(runningSum[i]), end(runningSum[i]), l));

        difference[i] = right - left;
    }

    long long numerator = 0, denominator = 1, singleQty = 0;
    for (const auto& d : difference)
    {
        numerator += d / 2;
        denominator = (denominator * modularMultiplicativeInverses[d / 2]) % modulo;
        singleQty += d % 2;
    }

    long long permutationsWithRepetions = ((factorialMods[numerator] * denominator) % modulo) * max(1LL, singleQty) % modulo;
    return permutationsWithRepetions;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    initialize(s);

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int l = stoi(first_multiple_input[0]);

        int r = stoi(first_multiple_input[1]);

        int result = answerQuery(l, r);

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
