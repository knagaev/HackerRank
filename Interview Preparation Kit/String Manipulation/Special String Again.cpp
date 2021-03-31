#include <bits/stdc++.h>

using namespace std;

// Complete the substrCount function below.
long substrCount(int n, string s) 
{
    long countSpecial = 0;
    int continuousChar[n];

    int lastPos = 0;
    int lenContinuous = 0;
    for(auto i = 1; i < n; ++i)
    {
        if(s[i] != s[lastPos])
        {
            lenContinuous = i - lastPos;
            countSpecial += lenContinuous * (lenContinuous + 1) / 2;
            continuousChar[lastPos] = lenContinuous;
            lastPos = i;
        }
    }

    lenContinuous = n - lastPos;
    countSpecial += lenContinuous * (lenContinuous + 1) / 2;
    continuousChar[lastPos] = lenContinuous;

    for(auto i = 1 - 1; i < n; ++i)
    {
        if(s[i] == s[i - 1])
            continuousChar[i] = continuousChar[i - 1];

        if(s[i - 1] == s[i + 1] && s[i] != s[i - 1]) 
        {
            countSpecial += min(continuousChar[i - 1], continuousChar[i + 1]);
        }

    }


    return countSpecial;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
