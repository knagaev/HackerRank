#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

long long getPairsQty(const vector<long>& arr1, const vector<long>& arr2)
{

    if (arr2.size() == 1)
    {
        return count(begin(arr1), end(arr1), 1L);
    }

    long long result = 0;
    if (arr1.size() == 1 && arr1.front() == 1L) // optimize for "the only one on the left" case
    {
        result = arr2.size();
    }
    else
    {
        auto maxValue = arr2.back();
        long lastA1 = 0;
        long lastDistance = 0;
        for (const auto& a1 : arr1)
        {
            if (lastA1 == a1)
                result += lastDistance;
            else
            {
                lastA1 = a1;
                auto upper = maxValue / a1;
                auto upperBound = upper_bound(begin(arr2), end(arr2), upper);
                if (upperBound == begin(arr2)) break;
                lastDistance = distance(begin(arr2), upperBound);
                result += lastDistance;
            }
        }
    }

    long long countOnesOnRight = count(begin(arr2), end(arr2), 1L);
    if(countOnesOnRight > 0)
        result += (1L == arr2.back()) ? countOnesOnRight * (countOnesOnRight - 1) / 2 : countOnesOnRight;

    return result;
}

vector<long>::const_iterator optimizedMaxElement(vector<long>::const_iterator beginIt, vector<long>::const_iterator endIt)
{
    auto middleIt = beginIt + (endIt - beginIt) / 2;

    auto optimizedMaxIt = beginIt;
    for (auto it = beginIt; it != endIt; ++it)
    {
        if (*it < *optimizedMaxIt) continue;

        if (*it > *optimizedMaxIt || abs(middleIt - it) < abs(optimizedMaxIt - it))
            optimizedMaxIt = it;
    }
    
    return optimizedMaxIt;
}

long long recursiveSolve(vector<long>::const_iterator beginIt, vector<long>::const_iterator endIt)
{
    if (distance(beginIt, endIt) < 2) return 0;

    auto maxElement = optimizedMaxElement(beginIt, endIt);

    vector<long> leftArr(beginIt, maxElement);
    sort(begin(leftArr), end(leftArr));

    vector<long> rightArr(maxElement, endIt);
    sort(begin(rightArr), end(rightArr));

    if (leftArr.empty() && rightArr.front() == rightArr.back())
    {
        if (rightArr.front() > 1)
            return 0L;
        else
            return rightArr.size() * (rightArr.size() - 1) /2;
    }

    long long result = 0;

    result += getPairsQty(leftArr, rightArr);

    result += recursiveSolve(beginIt, maxElement);
    result += recursiveSolve(next(maxElement), endIt);

    return result;
}

long long solve(const vector<long>& arr)
{
    return recursiveSolve(begin(arr), end(arr));
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string arr_count_temp;
    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long long result = solve(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
