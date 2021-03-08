#include <bits/stdc++.h>

using namespace std;

// Complete the anagram function below.
int anagram(string s) 
{
    if(s.length() % 2 != 0) return -1;
    
    map<char, int> first, second;
    for(size_t i = 0; i < s.length() / 2; ++i)
    {
        first[s[i]]++;
        second[s[s.length() / 2 + i]]++;
    }

    int result = 0;
    for(const auto& f : first)
    {
        result += max(0, f.second - second[f.first]); 
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = anagram(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
