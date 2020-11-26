#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the almostSorted function below.
void almostSorted(vector<int> arr) 
{
    // firstPos, lastPos 
    vector<pair<int, int>> ascSegments, descSegments;

    auto last = cbegin(arr);
    auto end = prev(cend(arr));
    bool wasAscending = *cbegin(arr) < *(next(cbegin(arr)));
    for (auto it = cbegin(arr); it != end; ++it)
    {
        bool ascending = *it < *(next(it));
        if (ascending != wasAscending)
        {
            if (wasAscending)
                ascSegments.push_back({ distance(cbegin(arr), last), distance(cbegin(arr), it) });
            else
                descSegments.push_back({ distance(cbegin(arr), last), distance(cbegin(arr), it) });

            wasAscending = ascending;
            last = it;
        }
    }

    if (wasAscending)
        ascSegments.push_back({ distance(cbegin(arr), last), distance(cbegin(arr), cend(arr)) - 1 });
    else
        descSegments.push_back({ distance(cbegin(arr), last), distance(cbegin(arr), cend(arr)) - 1});

    switch (descSegments.size())
    {
        case 1:
            {
                bool oneSegmentOk = true;
                if (descSegments[0].first != 0)
                    oneSegmentOk &= arr[descSegments[0].second] > arr[descSegments[0].first - 1];
                if (descSegments[0].second != arr.size() - 1)
                    oneSegmentOk &= arr[descSegments[0].first] < arr[descSegments[0].second + 1];
                if (oneSegmentOk)
                {
                    if (descSegments[0].second - descSegments[0].first == 1)
                    {
                        cout << "yes" << endl;
                        cout << "swap " << descSegments[0].first + 1 << " " << descSegments[0].second + 1 << endl;
                    }
                    else
                    {
                        cout << "yes" << endl;
                        cout << "reverse " << descSegments[0].first + 1 << " " << descSegments[0].second + 1 << endl;
                    }
                    return;
                }
            }
            break;
        case 2:
            if ( descSegments[0].second - descSegments[0].first == 1 
              && descSegments[1].second - descSegments[1].first == 1)
            {
                bool twoSegmentOk = true;
                twoSegmentOk &= arr[descSegments[0].first] > arr[descSegments[1].first];
                twoSegmentOk &= arr[descSegments[0].second] > arr[descSegments[1].second];
                if(descSegments[0].first != 0)
                    twoSegmentOk &= arr[descSegments[1].second] > arr[descSegments[0].first - 1];
                if(descSegments[1].second != arr.size() - 1)
                    twoSegmentOk &= arr[descSegments[0].first] < arr[descSegments[1].second + 1];

                if (twoSegmentOk)
                {
                    cout << "yes" << endl;
                    cout << "swap " << descSegments[0].first + 1 << " " << descSegments[1].second + 1 << endl;
                    return;
                }
            }
            break;
        default:
            break;

    }

    cout << "no" << endl;
    return;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
