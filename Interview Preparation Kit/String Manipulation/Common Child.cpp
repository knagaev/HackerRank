#include <bits/stdc++.h>

using namespace std;

// Complete the commonChild function below.
int commonChild(string s1, string s2) 
{
    auto s1Length = s1.length();
    auto s2Length = s2.length();
    
    vector<vector<int>> mat;
    mat.reserve(s1Length);
    
    for(const auto& c1 : s1)
    {
        vector<int> vec;
        vec.reserve(s2Length);
        int i = 0;
        for(const auto& c2 : s2)
        {
            if(c1 == c2)
            {
                auto lastSum = (!mat.empty() && i > 0) ? mat.back()[i - 1] + 1 : 1;
                vec.push_back(lastSum);
            }
            else
            {
                auto prevRow = !mat.empty() ? mat.back()[i] : 0;
                auto curRow =  (i > 0) ? vec[i - 1] : 0;
                vec.push_back(max(prevRow, curRow));       
            }
            ++i;
        }
        mat.push_back(vec);
    }
    
    int commonChildLength = mat.back().back();
  
    return commonChildLength;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";

    fout.close();

    return 0;
}
