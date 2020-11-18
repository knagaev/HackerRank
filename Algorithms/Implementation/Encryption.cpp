#include <bits/stdc++.h>

using namespace std;

// Complete the encryption function below.
string encryption(string s) 
{
    auto withoutSpaces = accumulate(begin(s), end(s),
        move(vector<char>()),
        [](auto&& acc, const auto& c) 
        {
            if (!isspace(c)) acc.push_back(c);
            return acc;
        }
    );

    auto upperEdge = static_cast<size_t>(ceil(pow(withoutSpaces.size(), .5)));

    stringstream ss;
    for (size_t i = 0; i < upperEdge; ++i)
    {
        for (size_t j = i; j < withoutSpaces.size(); j += upperEdge)
        {
            ss << withoutSpaces[j];
        }
        ss << " ";
    }
    return ss.str();
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = encryption(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
