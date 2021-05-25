#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

pair<vector<long>, long long> merge(const pair<vector<long>, long long>& leftPair, const pair<vector<long>, long long>& rightPair)
{
    long long countInv = leftPair.second + rightPair.second;
    auto& left = leftPair.first;
    auto& right = rightPair.first;

    vector<long> result(left.size() + right.size());

    auto lit = begin(left);
    auto rit = begin(right);
    auto it = begin(result);

    while (lit != end(left) && rit != end(right))
    {
        if (*lit <= *rit)
        {
            *it = *lit;
            ++lit;
        }
        else
        {
            *it = *rit;
            ++rit;
            countInv += distance(lit, end(left));
        }
        ++it;
    }

    copy(lit, end(left), it);
    copy(rit, end(right), it);

    return { result, countInv };
}

pair<vector<long>, long long> mergeSort(const vector<long>& arr, vector<long>::iterator lit, vector<long>::iterator rit)
{
    if (rit - lit < 2) return { vector<long>(lit, rit), 0 };

    auto mit = lit + (rit - lit) / 2;

    auto left = mergeSort(arr, lit, mit);
    auto right = mergeSort(arr, mit, rit);
    auto merged = merge(left, right);

    return merged;
}

// Complete the insertionSort function below.
long long insertionSort(vector<long> arr)
{
    auto result = mergeSort(arr, begin(arr), end(arr));

    return result.second;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    long t = stol(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<long> arr(n);

        for (int i = 0; i < n; i++) {
            long arr_item = stol(arr_temp[i]);

            arr[i] = arr_item;
        }

        long long result = insertionSort(arr);

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
