#include <bits/stdc++.h>

using namespace std;


long getN(int n, vector<long>& memo)
{
  if (n == 1) memo[n] = 1;
  if (n == 2) memo[n] = 2;
  if (n == 3) memo[n] = 4;

  if (memo[n] > 0) return memo[n];

  memo[n] = getN(n - 3, memo) + getN(n - 2, memo) + getN(n - 1, memo);

  return memo[n];
}

// Complete the stepPerms function below.
int stepPerms(int n) 
{
  vector<long> memo(n + 1, 0);
  
  return getN(n, memo) % 10000000007;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int s_itr = 0; s_itr < s; s_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int res = stepPerms(n);

        fout << res << "\n";
    }

    fout.close();

    return 0;
}
