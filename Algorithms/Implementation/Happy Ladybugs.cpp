#include <bits/stdc++.h>

using namespace std;

// Complete the happyLadybugs function below.
string happyLadybugs(string b) 
{
    map<char, int> charCounter;
    for (const auto& bi : b)
        ++charCounter[bi];

    if (charCounter['_'] == 0)
    {
        int adjCount = 0;
        char prevChar = '\0';
        for (const auto& bi : b)
        {
            if (bi != prevChar)
            {
                if (adjCount == 1)
                    return "NO";
                prevChar = bi;
                adjCount = 1;
            }
            else
                ++adjCount;
        }
        if (adjCount == 1)
            return "NO";
    }

    for (const auto& cc : charCounter)
    {
        if (cc.second == 1 && cc.first != '_')
            return "NO";
    }

    return "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int g;
    cin >> g;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int g_itr = 0; g_itr < g; g_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string b;
        getline(cin, b);

        string result = happyLadybugs(b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
