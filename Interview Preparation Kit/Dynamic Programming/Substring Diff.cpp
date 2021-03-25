#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int findMaxLength(int k, const string& a, const string& b, size_t aOffset, size_t bOffset)
{
    size_t startPos = 0;
    queue<int> chunks;

    size_t maxLength = 0;
    for (size_t i = 0; i < a.length() - max(aOffset, bOffset); i++)
    {
        if (a[aOffset + i] != b[bOffset + i])
        {
            if (k == 0)
            {
                startPos = i + 1;
            }
            else
            {
                if (chunks.size() == k)
                {
                    startPos = chunks.front() + 1;
                    chunks.pop();
                }
                chunks.push(i);
            }
        }
        maxLength = max(maxLength, i - startPos + 1);
    }

    return static_cast<int>(maxLength);
}

// Complete the substringDiff function below.
int substringDiff(int k, string s1, string s2) 
{
    int maxLength = 0;

    for (size_t i = 0; i < s1.size(); ++i) 
        maxLength = max(maxLength, findMaxLength(k, s1, s2, i, 0));

    for (size_t i = 0; i < s1.size(); ++i) 
        maxLength = max(maxLength, findMaxLength(k, s1, s2, 0, i));

    return maxLength;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string kS1S2_temp;
        getline(cin, kS1S2_temp);

        vector<string> kS1S2 = split_string(kS1S2_temp);

        int k = stoi(kS1S2[0]);

        string s1 = kS1S2[1];

        string s2 = kS1S2[2];

        int result = substringDiff(k, s1, s2);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
