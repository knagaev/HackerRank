#include <bits/stdc++.h>

using namespace std;

// Complete the palindromeIndex function below.
int palindromeIndex(string s) 
{
    int k = -1;
    int i = 0;
    int j = 1;

    while (i < (s.length() + 1) / 2)
    {
        if (s[i] != s[s.length() - i - j])
        {
            if (k != -1) break;
            k = i;
            j = 0;
        }
        ++i;
    }

    if (i == (s.length() + 1) / 2)
        return k;
    else
        return s.length() - k - 1;

    return -1;
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

        int result = palindromeIndex(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
