#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'downToZero' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */

vector<long> numberOfMoves = {0, 1, 2, 3};

void precompute(vector<long>& numberOfMoves, long n)
{
    if (numberOfMoves.size() <= n)
        numberOfMoves.resize(n + 1, -1L);

    for (long l = 2; l < n + 1; ++l)
    {
        if (numberOfMoves[l] < 0 ||                         // not inited
            numberOfMoves[l] > numberOfMoves[l - 1] + 1)    // or use more effective way through l - 1
            numberOfMoves[l] = numberOfMoves[l - 1] + 1;

        for (long m = 2; m <= l && (l * m < n + 1); ++m)
        {
            if (numberOfMoves[l * m] < 0 ||                     // not inited
                numberOfMoves[l * m] > numberOfMoves[l] + 1)    // or use more effective way through l = max(l, m)
                numberOfMoves[l * m] = numberOfMoves[l] + 1;
        }
    }
}

long downToZero(long n) 
{
    if (numberOfMoves.size() <= n)
        precompute(numberOfMoves, n);

    return numberOfMoves[n];
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        long result = downToZero(n);

        fout << result << "\n";
    }

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
