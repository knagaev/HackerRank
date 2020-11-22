#include <bits/stdc++.h>

using namespace std;

// Complete the appendAndDelete function below.
string appendAndDelete(string s, string t, int k) 
{

    if (k >= s.length() + t.length())
        return "Yes";

    size_t sameCharLength = 0;
    for(; sameCharLength < min(s.length(), t.length()); ++sameCharLength)
    {
        if (s[sameCharLength] != t[sameCharLength])
            break;
    }
    
    int minChanges = s.length() + t.length() - 2 * sameCharLength;
    if (k >= minChanges && (k - minChanges) % 2 == 0)
        return "Yes";

    return "No";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string t;
    getline(cin, t);

    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string result = appendAndDelete(s, t, k);

    fout << result << "\n";

    fout.close();

    return 0;
}
