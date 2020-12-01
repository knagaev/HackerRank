#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

// Complete the alternate function below.
int alternate(string s) 
{
    set<char> symbols(begin(s), end(s));
    vector<vector<vector<char>>> matrix(symbols.size(), vector<vector<char>>(symbols.size(), vector<char>()));

    for (const auto& c : s)
    {
        auto d = distance(cbegin(symbols), find(cbegin(symbols), cend(symbols), c));

        auto& row = matrix[d];
        for (auto it = begin(row); it != end(row); ++it)
        {
            if ((*it).empty())
                (*it).push_back(c);
            else
            {
                if ((*it).back() != c && (*it).back() != '\0')
                    (*it).push_back(c);
                else
                    (*it).push_back('\0');
            }
        }
        for (auto jt = begin(matrix); jt != end(matrix); ++jt)
        {
            auto& column = *(next(begin(*jt), d));
            if (column.empty())
                column.push_back(c);
            else
            {
                if(column.back() != c && column.back() != '\0')
                    column.push_back(c);
                else
                    column.push_back('\0');
            }
        }
    }

    size_t maxLength = 0;
    for (const auto& row : matrix)
    {
        for (const auto& v : row)
        {
            if (v.back() != '\0')
                maxLength = max(maxLength, v.size());
        }
    }
    return static_cast<int>(maxLength);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

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
