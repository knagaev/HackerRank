#include <bits/stdc++.h>

using namespace std;

bool isKaprekar(int i)
{
    int divisor = 10;
    while (i >= divisor)
        divisor *= 10;

    auto squared = static_cast<long long>(i) * static_cast<long long>(i);

    auto leftPart = squared / divisor;
    auto rightPart = squared % divisor;
    
    return leftPart + rightPart == i;
}

// Complete the kaprekarNumbers function below.
void kaprekarNumbers(int p, int q)
{
    bool invalidRange = true;
    for (int i = p; i <= q; ++i)
    {
        if (isKaprekar(i))
        {
            cout << i << " ";
            invalidRange = false;
        }
    }

    if (invalidRange)
        cout << "INVALID RANGE" << endl;
}

int main()
{
    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    kaprekarNumbers(p, q);

    return 0;
}
