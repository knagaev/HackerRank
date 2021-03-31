#include <bits/stdc++.h>

using namespace std;

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) 
{
    auto l = s.length();
    map<string, int> m;

    for(unsigned long i = 1; i < l; i++)
    {
        for(unsigned long j = 0; j < l - i + 1; j++)
        {
            auto substring = s.substr(j, i);
            sort(substring.begin(), substring.end());
            auto it = m.find(substring);
            if(it != m.end())
                (*it).second++;
            else
                m.insert({substring, 1});
        }
    }
    
    int anagramsNumber = 0;
    for(const auto& p : m)
    {
        if(p.second > 1)
            anagramsNumber += p.second * (p.second - 1) / 2;

        //cout << p.first << ' ' << p.second << endl;
    }
    
    //cout << endl;
    return anagramsNumber;
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

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
