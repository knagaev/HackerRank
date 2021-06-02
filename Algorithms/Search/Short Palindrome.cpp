#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'shortPalindrome' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

const long long modulo = 1000000007LL;

long shortPalindrome(string s)
{
    vector<long long> first(26, 0LL);
    vector<vector<long long>> second(26, 
                                     vector<long long>(26, 0LL));
    vector<vector<vector<long long>>> third(26, 
                                            vector<vector<long long>>(26, 
                                                                      vector<long long>(26, 0LL)));
    vector < vector<vector<vector<long long>>>> fourth(26, 
                                                       vector<vector<vector<long long>>>(26, 
                                                                                         vector<vector<long long>>(26, 
                                                                                                                   vector<long long>(26, 0LL))));

    for (const auto& ch : s)
    {
        auto num = ch - 'a';
        for (int i = 0; i < 26; ++i)
        {
            fourth[num][i][i][num] += third[num][i][i] % modulo;
            third[i][num][num] += second[i][num] % modulo;
            second[i][num] += first[i] % modulo;
        }
        ++first[num];
    }

    long long sum = 0;
    for (const auto& levelOne : fourth)
    {
        for (const auto& levelTwo : levelOne)
        {
            for (const auto& levelThree : levelTwo)
            {
                for (const auto& q : levelThree)
                {
                    sum += q % modulo;
                }
            }
        }
    }

    return (long)sum % modulo;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long result = shortPalindrome(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
