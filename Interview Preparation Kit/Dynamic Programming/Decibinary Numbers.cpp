#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'decibinaryNumbers' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER x as parameter.
 */

size_t N = 285133;
size_t M = 19;

long long tm = 0;

vector<vector<long long> > g(N + 1, vector<long long>(M + 1, 0));
vector<long long> gs;

void decibinaryNumbers_helper(string& db, long long d, long long n, size_t m) 
{

    // get n-th decibinary of decimal d
    if (n == 1 && g[d][1]) 
    {
        db += string(m - 1, '0') + to_string(d);
        return;
    }

    auto it = lower_bound(begin(g[d]), end(g[d]), n);
    int j = it - begin(g[d]);
    long long y0 = g[d][j - 1];
    long long y = y0;
    long long a = pow(2, j - 1);
    long long k = d - a;
    int c = 9;

    string s;
    while (k >= 0 && c--) 
    {
        y0 = y;
        y += g[k][j - 1];
        if (y >= n) 
        {
            s = to_string(9 - c);
            decibinaryNumbers_helper(s, k, n - y0, j - 1);
            if (db.size() && s.size() < m)
                s = string(m - s.size(), '0') + s;
            db += s;
            return;
        }
        k -= a;
    }
}

long long decibinaryNumbers(long long x) 
{
    if (x == 1) return 0;

    string db;
    auto it = lower_bound(begin(gs), end(gs), x);
    long long d = it - begin(gs);
    it--;
    decibinaryNumbers_helper(db, d, x - (*it), M);
    long long z;
    stringstream ss(db);
    ss >> z;
    return z;
}

void dp() 
{
    // the following procedure can be used to find minimum N and M
    // first use big N and M
    // once while exits, i is the minimum N, log2(i)+1 is the minimum M
    long long i = 0, x = 0;
    while (x < 1e16) 
    {
        g[i][1] = (i >= 0 && i <= 9);
        for (size_t j = 2; j <= M; j++) 
        {
            long long a = pow(2, j - 1);
            long long k = i;
            int c = 10;
            while (k >= 0 && c--) 
            {
                g[i][j] += g[k][j - 1];
                k -= a;
            }
        }
        x += g[i][M];
        gs.push_back(x);
        i++;
    }
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    dp();
    for (int q_itr = 0; q_itr < q; q_itr++) {
        string x_temp;
        getline(cin, x_temp);

        long long x = stoll(ltrim(rtrim(x_temp)));

        long long result = decibinaryNumbers(x);

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
