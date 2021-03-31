#include <bits/stdc++.h>

using namespace std;

// Complete the makeAnagram function below.
int makeAnagram(string a, string b) 
{
    map<char, int> ma, mb; 

    for(char& c : a)
        ma[c]++;
    for(char& c : b)
        mb[c]++;

    int minDeletions = 0;
    for(const auto& ca : ma)
    {
        auto diff = ca.second - mb[ca.first];
        if(diff > 0) 
            minDeletions += diff;
    }

    for(const auto& cb : mb)
    {
        auto diff = cb.second - ma[cb.first];
        if(diff > 0) 
            minDeletions += diff;
    }

    return minDeletions;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a;
    getline(cin, a);

    string b;
    getline(cin, b);

    int res = makeAnagram(a, b);

    fout << res << "\n";

    fout.close();

    return 0;
}
