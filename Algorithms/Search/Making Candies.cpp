#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

template<class T>
T addWithLimit(T lhs, T rhs)
{
    if (lhs > 0 && rhs > numeric_limits<T>::max() - lhs)
        return numeric_limits<T>::max();
    else
        return lhs + rhs;
}

template<class T>
T multWithLimit(T lhs, T rhs)
{
    if (rhs == 0) return 0;
    if (lhs > numeric_limits<T>::max() / rhs)
        return numeric_limits<T>::max();
    else
        return lhs * rhs;
}

long long minimumPasses(long long m, long long w, long long p, long long n)
{
    auto candies = 0LL;
    auto passesWithInvestments = 0LL;

    auto offset = 0LL;
    auto passesWithoutAdditionalSpend = numeric_limits<long long>::max();

    while (candies < n && passesWithoutAdditionalSpend > passesWithInvestments)
    {
        auto withoutSpend = (p > candies) ? max(1LL, (min(p, n) - candies) / multWithLimit(m, w)) : 0; // if lack of candies for buying, we get candies withoutSpend times
        //candies += m * w * withoutSpend;
        candies += multWithLimit(multWithLimit(m, w), withoutSpend);
        passesWithInvestments += withoutSpend;

        if (candies >= n) break;

        auto newUnits = m + w + candies / p;
        candies %= p;
        if (m > w) // add to bigger
        {
            m = max(m, (newUnits + 1) / 2);
            w = newUnits - m;
        }
        else
        {
            w = max(w, (newUnits + 1) / 2);
            m = newUnits - w;
        }
        candies = addWithLimit(candies, multWithLimit(m, w));
        ++passesWithInvestments;

        offset = static_cast<long long>(ceill(1. * (n - candies) / (m * w)));
        passesWithoutAdditionalSpend = min(passesWithoutAdditionalSpend, passesWithInvestments + offset);
    }

    return min(passesWithInvestments, passesWithoutAdditionalSpend);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string mwpn_temp;
    getline(cin, mwpn_temp);

    vector<string> mwpn = split_string(mwpn_temp);

    long long m = stol(mwpn[0]);

    long long w = stol(mwpn[1]);

    long long p = stol(mwpn[2]);

    long long n = stol(mwpn[3]);

    long long result = minimumPasses(m, w, p, n);

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
