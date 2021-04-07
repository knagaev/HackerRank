#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the riddle function below.
vector<long> riddle(vector<long> arr) 
{
    map<long, long> windowSizes;

    stack<long> st;
    size_t i = 0;
    while(i < arr.size())
    {
        if (st.empty() || arr[i] >= arr[st.top()])
        {
            st.push(i);
            ++i;
        }
        else
        {
            int curMaxPosition = st.top();
            st.pop();
            int curMaxWindowSize = st.empty() ? i : (i - st.top() - 1);
            auto it = windowSizes.find(arr[curMaxPosition]);
            if (it == end(windowSizes) || windowSizes[arr[curMaxPosition]] < curMaxWindowSize)
                windowSizes[arr[curMaxPosition]] = curMaxWindowSize;
        }
    }

    while (!st.empty())
    {
        int curMaxPosition = st.top();
        st.pop();
        int curMaxWindowSize = st.empty() ? arr.size() : (arr.size() - st.top() - 1);
        auto it = windowSizes.find(arr[curMaxPosition]);
        if (it == end(windowSizes) || windowSizes[arr[curMaxPosition]] < curMaxWindowSize)
            windowSizes[arr[curMaxPosition]] = curMaxWindowSize;
    }

    map<long, long> invertedWindowSizes;
    for (const auto& ws : windowSizes)
    {
        auto it = invertedWindowSizes.find(ws.second);
        if (it == end(invertedWindowSizes) || invertedWindowSizes[ws.second] < ws.first)
            invertedWindowSizes[ws.second] = ws.first;
    }

    vector<long> result(arr.size());
    long maxValue = 0;
    for (size_t i = arr.size(); i > 0; --i)
    {
        auto it = invertedWindowSizes.find(i);
        if (it != end(invertedWindowSizes))
            maxValue = max(maxValue, (*it).second);
        result[i - 1] = maxValue;
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<long> res = riddle(arr);

    for (int i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

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
