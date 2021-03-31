#include <bits/stdc++.h>

using namespace std;

// Complete the abbreviation function below.
string abbreviation(string a, string b) 
{
    auto n = a.length() + 1;
    auto m = b.length() + 1;

    vector<vector<bool>> check(n, vector<bool>(m, false));
    check[0][0] = true;

    for (size_t i = 1; i < n; i++)
    {
        if (islower(a[i - 1])) 
            check[i][0] = true;
        else 
            break;
    }

    for (size_t i = 1; i < n; i++)
    {
        for (size_t j = 1; j < m; j++)
        {
            if (isupper(a[i - 1]))
                check[i][j] = a[i - 1] == b[j - 1] && check[i - 1][j - 1];
            else if (i != 0 && j != 0)
            {
                if (toupper(a[i - 1]) == b[j - 1] && check[i - 1][j - 1])
                    check[i][j] = true;
                else
                    check[i][j] = check[i - 1][j];
            }
        }
    }
    
    return (check[n - 1][m - 1]) ? "YES" : "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string a;
        getline(cin, a);

        string b;
        getline(cin, b);

        string result = abbreviation(a, b);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
