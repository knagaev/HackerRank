#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

long lilysHomework(vector<long> arr)
{
    map<long, long> positionsAsc;

    long i = 0;
    for (const auto& a : arr)
        positionsAsc[a] = i++;

    auto arrDesc(arr);
    auto positionsDesc(positionsAsc);

    long swapsAsc = 0;
    long curPosition = 0;
    for (auto it = begin(positionsAsc); it != end(positionsAsc); ++it)
    {
        if (it->second > curPosition)
        {
            ++swapsAsc;
            arr[it->second] = arr[curPosition];
            positionsAsc[arr[curPosition]] = it->second;
        }
        ++curPosition;
    }

    curPosition = 0;
    long swapsDesc = 0;
    for (auto it = rbegin(positionsDesc); it != rend(positionsDesc); ++it)
    {
        if (it->second > curPosition)
        {
            ++swapsDesc;
            arrDesc[it->second] = arrDesc[curPosition];
            positionsDesc[arrDesc[curPosition]] = it->second;
        }
        ++curPosition;
    }
    return min(swapsAsc, swapsDesc);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long result = lilysHomework(arr);

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
