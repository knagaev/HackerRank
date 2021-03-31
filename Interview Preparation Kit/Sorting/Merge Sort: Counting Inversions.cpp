#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void printArr(const vector<int>& arr, char a)
{
    cout << a << " ";
    for(const auto& c : arr)
        cout << c << " ";
    cout << endl;
}

// Complete the countInversions function below.
long countInversions(vector<int>& arr) 
{
    auto arrSize = arr.size();
    if(arrSize < 2) return 0;

    auto lSize = arrSize / 2;
    auto rSize = arrSize - lSize;

    vector<int> lArr(arr.begin(), next(arr.begin(), lSize));
    vector<int> rArr(next(arr.begin(), lSize), arr.end());

//    printArr(lArr, 'l');
//    printArr(rArr, 'r');

    auto inversions = countInversions(lArr) + countInversions(rArr);
    
    size_t i1 = 0, i2 = 0;

    for(size_t i = 0; i < arrSize; ++i)
    {
        if(i1 < lSize && (i2 >= rSize || lArr[i1] <= rArr[i2]))
        {
            arr[i] = lArr[i1];
            inversions += i2;
            ++i1;
        }
        else
        {
            if(i2 < rSize)
            {
                arr[i] = rArr[i2];
                ++i2;
            }
        }
    }
        
//    cout << "i " << inversions << endl;

    return inversions;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
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

        long result = countInversions(arr);

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
