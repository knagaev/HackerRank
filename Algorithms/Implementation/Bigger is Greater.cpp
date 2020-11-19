#include <bits/stdc++.h>

using namespace std;

// Complete the biggerIsGreater function below.
string biggerIsGreater(string w) 
{
    for (auto it = rbegin(w); it != prev(rend(w)); ++it)
    {
        if (*it > *next(it))
        {   
            auto nextBigger = upper_bound(rbegin(w), next(it), *next(it));
            swap(*nextBigger, *next(it));
            sort(rbegin(w), next(it), greater<char>());
            return w;
        }
    }

    return "no answer";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int T;
    cin >> T;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
