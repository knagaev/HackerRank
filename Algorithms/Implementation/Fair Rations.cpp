#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the fairRations function below.
string fairRations(vector<int> B) 
{
    auto countOdd = count_if(begin(B), end(B),
        [](const auto& b) { return b % 2 == 1; }
        );

    if (countOdd % 2 == 1) return "NO";

    int needLoafs = 0;
    
    auto leftOdd = find_if(begin(B), end(B),
        [](const auto& b) { return b % 2 == 1; }
    );
    while (leftOdd != end(B))
    {
        auto rightOdd = find_if(next(leftOdd), end(B),
            [](const auto& b) { return b % 2 == 1; }
        );

        needLoafs += 2 * distance(leftOdd, rightOdd);

        leftOdd = find_if(next(rightOdd), end(B),
            [](const auto& b) { return b % 2 == 1; }
        );
    }
    return to_string(needLoafs);
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string B_temp_temp;
    getline(cin, B_temp_temp);

    vector<string> B_temp = split_string(B_temp_temp);

    vector<int> B(N);

    for (int i = 0; i < N; i++) {
        int B_item = stoi(B_temp[i]);

        B[i] = B_item;
    }

    string result = fairRations(B);

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
