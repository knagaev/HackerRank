#include <bits/stdc++.h>

using namespace std;

// Complete the strangeCounter function below.
long strangeCounter(long t) 
{
    auto triples = (t - 1) / 3;
    auto resets = static_cast<long>(log2(triples + 1));
    auto resetValue = pow(2, resets);
    auto runningSum = (resetValue - 1) * 3;
    auto remainder = resetValue * 3 - (t - runningSum) + 1;

    return static_cast<long>(remainder);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    long t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = strangeCounter(t);

    fout << result << "\n";

    fout.close();

    return 0;
}
