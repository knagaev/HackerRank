#include <bits/stdc++.h>

using namespace std;

// Complete the candies function below.
long candies(int n, vector<int> arr) 
{
    list<long> candies {1L};

    for (auto itA = next(begin(arr)); itA != end(arr); ++itA)
    {
        if (*itA > *prev(itA))
            candies.push_back(candies.back() + 1L);
        else
            candies.push_back(1L);
    }

    auto itC = prev(end(candies));
    for (auto itA = prev(end(arr)); itA != begin(arr); --itA, --itC)
    {
        if (*prev(itA) > *itA && *itC >= *prev(itC))
            *prev(itC) = *itC + 1;
    }
    return accumulate(begin(candies), end(candies), 0L);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item;
        cin >> arr_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        arr[i] = arr_item;
    }

    long result = candies(n, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
