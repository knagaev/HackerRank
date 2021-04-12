#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the poisonousPlants function below.
int poisonousPlants(vector<int> p)
{
    list<queue<int>> chains;

    int prevPlant = 0;
    for (const auto& curPlant : p)
    {
        if (curPlant > prevPlant)
            chains.push_back(queue<int>());

        chains.back().push(curPlant);
        prevPlant = curPlant;
    }

    int turns = 0;
    while (chains.size() > 1)
    {
        for (auto it = prev(end(chains)); it != begin(chains); )
        {
            auto& curChain = *it;
            auto& prevChain = *prev(it);
            curChain.pop();
            if (!curChain.empty() && curChain.front() <= prevChain.back())
            {
                while (!curChain.empty())
                {
                    prevChain.push(curChain.front());
                    curChain.pop();
                }
            }
            if (curChain.empty())
                it = chains.erase(it);

            it = prev(it);
        }
        ++turns;
    }

    return turns;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string p_temp_temp;
    getline(cin, p_temp_temp);

    vector<string> p_temp = split_string(p_temp_temp);

    vector<int> p(n);

    for (int i = 0; i < n; i++) {
        int p_item = stoi(p_temp[i]);

        p[i] = p_item;
    }

    int result = poisonousPlants(p);

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
