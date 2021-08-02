#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'travelAroundTheWorld' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY a
 *  2. INTEGER_ARRAY b
 *  3. LONG_INTEGER c
 */

int travelAroundTheWorld(vector<long long> fuels, vector<long long> expenses, long long tank) 
{
    transform(begin(fuels), end(fuels), begin(fuels), [&tank](const auto& fuel) { return min(fuel, tank); });

    for (const auto& e : expenses)
        if (e > tank) return 0;

    vector<long long> minStartFuels(fuels.size() + 1);
    vector<long long> leftInTank(fuels.size() + 1);
    vector<long long> maxInTank(fuels.size() + 1);

    for (size_t i = 1; i < fuels.size(); ++i)
    {
        if (expenses[i - 1] > fuels[i - 1] + leftInTank[i - 1])
        {
            if (tank - maxInTank[i - 1] < expenses[i - 1] - leftInTank[i - 1] - fuels[i - 1])
                return 0;

            minStartFuels[i] = minStartFuels[i - 1] + expenses[i - 1] - leftInTank[i - 1] - fuels[i - 1];

            leftInTank[i] = 0;

            maxInTank[i] = max(maxInTank[i - 1] + expenses[i - 1] - leftInTank[i - 1] - fuels[i - 1], expenses[i - 1]);
        }
        else
        {
            minStartFuels[i] = minStartFuels[i - 1];
            leftInTank[i] = min(leftInTank[i - 1] + fuels[i - 1], tank) - expenses[i - 1];
            maxInTank[i] = max(maxInTank[i - 1], min(leftInTank[i - 1] + fuels[i - 1], tank));
        }
    }

    vector<long long> minStartFuels2(fuels.size() + 1);
    vector<long long> leftInTank2(fuels.size() + 1);
    vector<long long> maxInTank2(fuels.size() + 1);

    for (size_t i = fuels.size() - 1; i > 0; --i)
    {
        if (minStartFuels2[i + 1] + expenses[i] > tank)
            return 0;

        if (expenses[i] > fuels[i])
        {
            minStartFuels2[i] = minStartFuels2[i + 1] + expenses[i] - fuels[i];
            leftInTank2[i] = leftInTank2[i + 1];
            maxInTank2[i] = max(maxInTank2[i + 1], fuels[i] + minStartFuels2[i]);
        }

        else if (fuels[i] - expenses[i] > minStartFuels2[i + 1])
        {
            minStartFuels2[i] = 0;
            leftInTank2[i] = leftInTank2[i + 1] + min(tank - maxInTank2[i + 1], fuels[i] - expenses[i] - minStartFuels2[i + 1]);
            maxInTank2[i] = max(fuels[i], min(tank, maxInTank2[i + 1] + fuels[i] - expenses[i] - minStartFuels2[i + 1]));
        }
        else
        {
            minStartFuels2[i] = minStartFuels2[i + 1] + expenses[i] - fuels[i];
            leftInTank2[i] = leftInTank2[i + 1];
            maxInTank2[i] = max(maxInTank2[i + 1], minStartFuels2[i] + fuels[i]);
        }
    }

    int result = 0;

    if (minStartFuels[1] == 0 and leftInTank[1] >= minStartFuels2[1])
        result = 1;

    for (size_t i = 1; i < fuels.size(); ++i)
    {
        if (minStartFuels2[i] == 0 and leftInTank2[i] >= minStartFuels[i])
            ++result;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    long long c = stoll(first_multiple_input[1]);

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<long long> a(n);

    for (int i = 0; i < n; i++)
        a[i] = stoll(a_temp[i]);

    string b_temp_temp;
    getline(cin, b_temp_temp);

    vector<string> b_temp = split(rtrim(b_temp_temp));

    vector<long long> b(n);

    for (int i = 0; i < n; i++)
        b[i] = stoll(b_temp[i]);

    int result = travelAroundTheWorld(a, b, c);

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
