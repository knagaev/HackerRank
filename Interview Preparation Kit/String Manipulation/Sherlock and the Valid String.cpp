#include <bits/stdc++.h>

using namespace std;

// Complete the isValid function below.
string isValid(string s) 
{
    map<char, long> freq;

    for(const auto& c : s)
    {
        freq[c]++;
    }
    
    map<long, long> invFreq;
    for(const auto& f : freq)
    {
        invFreq[f.second]++;
    }

    if(invFreq.size() == 1)
        return "YES";

    if(invFreq.size() == 2)
    {
        if(invFreq.begin()->first == 1 && invFreq.begin()->second == 1)
            return "YES";

        if(next(invFreq.begin())->second == 1)
        {
            if(next(invFreq.begin())->first == (invFreq.begin()->first + 1))
                return "YES";
        }
    }

    return "NO";

    /*
    long allFreq = 0;
    bool firstTime = false;
    for(const auto& f : freq)
    {
        if(allFreq == f.second) continue;

        if(allFreq == 0)
        {
            allFreq = f.second;
        }
        else
        {
            if(firstTime || (allFreq + 1 != f.second && allFreq != f.second + 1))
            {
                return "NO";
            }

            firstTime = true;
        }
    }
    return "YES";
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
