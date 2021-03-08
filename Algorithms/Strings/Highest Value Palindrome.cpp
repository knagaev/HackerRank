#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the highestValuePalindrome function below.
string highestValuePalindrome(string s, int n, int k)
{
    string str(s);

    if (s.length() == 1 && k > 0) return "9";

    set<size_t> positions;
    int changes = 0;
    for (size_t i = 0; i < str.length() / 2; ++i)
    {
        if (str[i] != str[str.length() - i - 1])
        {
            positions.insert(i);
            if (str[i] > str[str.length() - i - 1])
                str[str.length() - i - 1] = str[i];
            else
                str[i] = str[str.length() - i - 1];
        }
    }
    
    int remainder = k - positions.size();

    if (remainder < 0) return "-1";

    int j = 0;
    int i = 0;
    while (j < remainder && i < (str.length() + 1) / 2)
    {
        if (str[i] != '9')
        {
            if (positions.find(i) == end(positions))
            {
                if (str.length() % 2 == 1 && i == str.length() / 2)
                {
                    str[i] =  '9';
                    ++j;
                }
                else
                {
                    if (remainder - j >= 2)
                    {
                        str[i] = str[str.length() - i - 1] = '9';
                        j += 2;
                    }
                    else
                    {
                        auto it = positions.upper_bound(i);
                        if (it != end(positions))
                        {
                            str[i] = str[str.length() - i - 1] = '9';
                            ++j;
                        }
                    }
                }
            }
            else
            {
                str[i] = str[str.length() - i - 1] = '9';
                ++j;
            }
        }
        ++i;
    }

    return str;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

    fout << result << "\n";

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
